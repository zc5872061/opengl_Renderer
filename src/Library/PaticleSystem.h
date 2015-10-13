//
//  PaticleSystem.h
//  OglRenderer
//
//  Created by Chukie on 15/10/13.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#pragma once

#include "Common.h"
#include "DrawableGameComponent.h"
#include "VertexDeclarations.h"
#include "PaticleUpdateEffect.h"
#include "BillboardEffect.h"
#include "RandomTexture.h"

#define MAX_PARTICLES 1000
#define PARTICLE_LIFETIME 10.0f

#define PARTICLE_TYPE_LAUNCHER 0.0f
#define PARTICLE_TYPE_SHELL 1.0f
#define PARTICLE_TYPE_SECONDARY_SHELL 2.0f

using namespace Library;

namespace Library{
    
    struct Particle
    {
        float Type;
        glm::vec3 Pos;
        glm::vec3 Vel;
        float LifetimeMillis;
    };
    
    
    class PaticleSystem:public DrawableGameComponent
    {
    public:
        PaticleSystem(Game* game, Camera* camera);
        ~PaticleSystem();
        virtual void Initialize() override;
        virtual void Draw(GameTime gametime) override;
    protected:
        enum VertexAttribute
        {
            VertexAttributePosition = 0,
            VertexAttributeType = 1,
            VertexAttributeVel = 2,
            VertexAttributeLifetimeMillis = 3
        };
        
        void UpdateParticles(float DeltaTimeMillis);
        void RenderParticles(const glm::mat4& VP, const glm::vec3& CameraPos);
        
        PaticleUpdateEffect* mShaderProgram;
        BillboardEffect* mBillboardShaderProgram;
        GLuint mVertexArrayObject;
        GLuint mVertexBuffer;
        RandomTexture mRandomTexture;
        
        bool m_isFirst;
        GLuint mTexture;
        unsigned int m_currVB;
        unsigned int m_currTFB;
        GLuint m_particleBuffer[2];
        GLuint m_transformFeedback[2];
        float m_time;
    };
}

