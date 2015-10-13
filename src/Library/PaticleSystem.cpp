//
//  PaticleSystem.cpp
//  OglRenderer
//
//  Created by Chukie on 15/10/13.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "PaticleSystem.h"
#include "SOIL.h"
#include "Camera.h"

namespace Library {
    PaticleSystem::PaticleSystem(Game* game, Camera* camera):
    DrawableGameComponent(game,camera),
    mBillboardShaderProgram(nullptr),
    mShaderProgram(nullptr),
    mVertexArrayObject(-1),
    mVertexBuffer(-1),
    m_time(0),
    m_currVB(0),
    m_currTFB(1)
    {
        
    }
    
    PaticleSystem::~PaticleSystem()
    {
        
    }
    
    void PaticleSystem::Initialize()
    {
        
        mTexture = SOIL_load_OGL_texture(fireImg, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB );
        
        Particle paticles[MAX_PARTICLES];
        ZERO_MEM(paticles);
        paticles[0].Type = PARTICLE_TYPE_LAUNCHER;
        paticles[0].Pos = glm::vec3(0.0f, 0.0f, 1.0f);
        paticles[0].Vel = glm::vec3(0.0f, 0.0001f, 0.0f);
        paticles[0].LifetimeMillis = 0.0f;
        
        //create array object
        glGenVertexArrays(1, &mVertexArrayObject);
        glBindVertexArray(mVertexArrayObject);
        glVertexAttribPointer(VertexAttributeType,1,GL_FLOAT,GL_FALSE,sizeof(VertexPaticle),(void*)offsetof(VertexPaticle, Type));
        glVertexAttribPointer(VertexAttributePosition,3,GL_FLOAT,GL_FALSE,sizeof(VertexPaticle),(void*)offsetof(VertexPaticle,Position));
        glVertexAttribPointer(VertexAttributeVel,3,GL_FLOAT,GL_FALSE,sizeof(VertexPaticle),(void*)offsetof(VertexPaticle, Velocity));
        glVertexAttribPointer(VertexAttributeLifetimeMillis,1,GL_FLOAT,GL_FALSE,sizeof(VertexPaticle),(void*)offsetof(VertexPaticle, Age));
        glBindVertexArray(0);
        
        glGenTransformFeedbacks(2, m_transformFeedback);
        glGenBuffers(2, m_particleBuffer);
        
        FOR(i, 2)
        {
            glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[i]);
            glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(paticles), paticles, GL_DYNAMIC_DRAW);
            glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_particleBuffer[i]);
        }
        //particls shader
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,PaticleUpVstr));
        shaders.push_back(ShaderDefinition(GL_GEOMETRY_SHADER,PaticleUpGstr));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,PaticleUpFstr));
        
        mShaderProgram = new PaticleUpdateEffect();
        mShaderProgram->BuildProgram(shaders);
        mShaderProgram->Initialize(mVertexArrayObject);
        const GLchar* Varyings[4];
        Varyings[0] = "Type1";
        Varyings[1] = "Position1";
        Varyings[2] = "Velocity1";
        Varyings[3] = "Age1";
        
        glTransformFeedbackVaryings(mShaderProgram->Program(), 4, Varyings, GL_INTERLEAVED_ATTRIBS);
        
        
        (*mShaderProgram->gRandomTexture())<<RANDOM_TEXTURE_UNIT_INDEX;
        (*mShaderProgram->gLauncherLifetime())<<100.0f;
        (*mShaderProgram->gShellLifetime())<<10000.0f;
        (*mShaderProgram->gSecondaryShellLifetime())<<2500.0f;
        
        if (!mRandomTexture.InitRandomTexture(1000)) {
            assert(true);
        }
        
        mRandomTexture.Bind(RANDOM_TEXTURE_UNIT);
        
        //billboard shader
        std::vector<ShaderDefinition> billboardShaders;
        billboardShaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,BillboardVstr));
        billboardShaders.push_back(ShaderDefinition(GL_GEOMETRY_SHADER,BillboardGstr));
        billboardShaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,BillboardFstr));
        
        mBillboardShaderProgram = new BillboardEffect();
        mBillboardShaderProgram->BuildProgram(billboardShaders);
        mBillboardShaderProgram->Initialize(mVertexArrayObject);
    }
    
    void PaticleSystem::Draw(GameTime gametime)
    {
        m_time += gametime.ElapsedGameTime();
        UpdateParticles(m_time);    
        
        glm::mat4 VP = mCamera->ProjectionMatrix();
        glm::vec3 CameraPos = mCamera->Position();
        
        
        RenderParticles(VP, CameraPos);
        m_currVB = m_currTFB;
        m_currTFB = (m_currTFB + 1) & 0x1;
    }
    
    void PaticleSystem::UpdateParticles(float DeltaTimeMillis)
    {
        glBindVertexArray(mVertexArrayObject);
        mShaderProgram->Use();
        (*mShaderProgram->gTime())<<m_time;
        (*mShaderProgram->gDeltaTimeMillis())<<DeltaTimeMillis;
        mRandomTexture.Bind(RANDOM_TEXTURE_UNIT);
        glEnable(GL_RASTERIZER_DISCARD);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[m_currVB]);
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[m_currTFB]);
        
        glEnableVertexAttribArray(VertexAttributePosition);
        glEnableVertexAttribArray(VertexAttributeType);
        glEnableVertexAttribArray(VertexAttributeVel);
        glEnableVertexAttribArray(VertexAttributeLifetimeMillis);
        
        //draw
        glBeginTransformFeedback(GL_POINTS);
        if (m_isFirst) {
            glDrawArrays(GL_POINTS, 0, 1);
            
            m_isFirst = false;
        }
        else {
            glDrawTransformFeedback(GL_POINTS, m_transformFeedback[m_currVB]);
        }
        glEndTransformFeedback();
        
        
        glDisableVertexAttribArray(VertexAttributePosition);
        glDisableVertexAttribArray(VertexAttributeType);
        glDisableVertexAttribArray(VertexAttributeVel);
        glDisableVertexAttribArray(VertexAttributeLifetimeMillis);
        glBindVertexArray(0);
    }
    
    void PaticleSystem::RenderParticles(const glm::mat4& VP, const glm::vec3& CameraPos)
    {
        glBindVertexArray(mVertexArrayObject);
        mBillboardShaderProgram->Use();
        glm::mat4 vp = mCamera->ViewProjectionMatrix();
        (*mBillboardShaderProgram->gVP())<<vp;
        (*mBillboardShaderProgram->gCameraPos())<<mCamera->Position();
        
        glBindTexture(GL_TEXTURE_2D, mTexture);
        
        glDisable(GL_RASTERIZER_DISCARD);
        glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[m_currTFB]);
        
        glEnableVertexAttribArray(VertexAttributePosition);
        glVertexAttribPointer(VertexAttributePosition,3,GL_FLOAT,GL_FALSE,sizeof(VertexPaticle),(void*)offsetof(VertexPaticle,Position));
        glDrawTransformFeedback(GL_POINTS, m_transformFeedback[m_currTFB]);
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }
}