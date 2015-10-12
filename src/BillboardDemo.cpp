//
//  BillboardDemo.cpp
//  OglRenderer
//
//  Created by Chukie on 15/10/12.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "BillboardDemo.h"
#include "SOIL.h"
#include "Camera.h"

namespace Rendering {
    BillboardDemo::BillboardDemo(Game* game, Camera* camera):
    DrawableGameComponent(game,camera),
    mVertexArrayObject(-1),
    mVertexBuffer(-1),
    mTexture(-1)
    {
        mShaderProgram = new BillboardEffect;
    }
    
    BillboardDemo::~BillboardDemo()
    {
        
    }
    
    void BillboardDemo::Initialize()
    {
         mTexture = SOIL_load_OGL_texture(testImg, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB );
        
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,BillboardVstr));
        shaders.push_back(ShaderDefinition(GL_GEOMETRY_SHADER,BillboardGstr));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,BillboardFstr));
        
        mShaderProgram->BuildProgram(shaders);
        glGenVertexArrays(1, &mVertexArrayObject);
        mShaderProgram->Initialize(mVertexArrayObject);
        glBindVertexArray(0);
        // Create the vertex buffer
        
        VertexPosition vertices[10*10];
        
        FOR(i, 10)
        {
            FOR(j, 10)
            {
                VertexPosition pos(glm::vec4(1.5*i,0.0,1.5*j,1.0));
                vertices[j*10+i] = pos;
            }
        }
        
        mShaderProgram->CreateVertexBuffer(vertices, sizeof(vertices), mVertexBuffer);
    }
    
    void BillboardDemo::Draw(GameTime gametime)
    {
        glEnable(GL_DEPTH);
        mShaderProgram->Use();
        glBindVertexArray(mVertexArrayObject);
        
        glm::mat4 vp = mCamera->ViewProjectionMatrix();
        (*mShaderProgram->gVP())<<vp;
        (*mShaderProgram->gCameraPos())<<mCamera->Position();
        
        glBindTexture(GL_TEXTURE_2D, mTexture);
        
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,mVertexBuffer);
        glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,0);
        glPointSize(80.0f);
        glDrawArrays(GL_POINTS, 0, 10);
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
        
    }
}