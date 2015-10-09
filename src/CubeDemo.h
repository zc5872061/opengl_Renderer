//
//  CubeDemo.h
//  test
//
//  Created by Chukie on 15/9/8.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#pragma once

#include "DrawableGameComponent.h"
#include "ShaderProgram.h"

using namespace Library;

namespace Rendering
{
    class CubeDemo : public DrawableGameComponent
    {
    public:
        CubeDemo(Game* game, Camera* camera);
        ~CubeDemo();
        
        virtual void Initialize() override;
        virtual void Draw(GameTime gametime) override;
        
    private:
        enum VertexAttribute
        {
            VertexAttributePosition = 0,
            VertexAttributeColor = 1
        };
        
        CubeDemo();
        CubeDemo(const CubeDemo& rhs);
        CubeDemo& operator=(const CubeDemo& rhs);
        
        static const GLfloat RotationRate;
        
        ShaderProgram* mShaderProgram;
        GLuint mVertexArrayObject;
        GLuint mVertexBuffer;
        GLuint mIndexBuffer;
        GLint mWorldViewProjectionLocation;
        glm::mat4 mWorldMatrix;
    };
}

