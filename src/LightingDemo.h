//
//  LightingDemo.h
//  OglRenderer
//
//  Created by Chukie on 15/10/15.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#pragma once

#include "DrawableGameComponent.h"
#include "ShaderProgram.h"
#include "Camera.h"

using namespace Library;

namespace Rendering
{
    class LightingDemo : public DrawableGameComponent
    {
    public:
        LightingDemo(Game* game, Camera* camera);
        ~LightingDemo();
        
        virtual void Initialize() override;
        virtual void Draw(GameTime gametime) override;
        
    private:
        
        ShaderProgram* mShaderProgram1;
        GLuint mVAO1;
        GLuint mVBO1;
        
        ShaderProgram* mShaderProgram2;
        GLuint mVAO2;
        GLuint mVBO2;
        
        GLuint mDiffuseMap;
        GLuint mSpecularMap;
        GLuint mEmissionMap;
        
    };
}

