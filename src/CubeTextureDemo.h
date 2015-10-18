//
//  CubeTextureDemo.h
//  OglRenderer
//
//  Created by Chukie on 15/10/13.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once

#include "DrawableGameComponent.h"
#include "ShaderProgram.h"


using namespace Library;

namespace Rendering
{
    class CubeTextureDemo : public DrawableGameComponent
    {
    public:
        CubeTextureDemo(Game* game, Camera* camera);
        ~CubeTextureDemo();
        
        virtual void Initialize() override;
        virtual void Draw(GameTime gametime) override;
        
    private:
        CubeTextureDemo();
        CubeTextureDemo(const CubeTextureDemo& rhs);
        CubeTextureDemo& operator=(const CubeTextureDemo& rhs);
        ShaderProgram* mShaderProgram;
        GLuint mVBO;
        GLuint mVAO;
        GLuint mColorTexture;
        GLuint mWorldViewProjectionLocation;
        glm::mat4 mWorldMatrix;
    };
}
