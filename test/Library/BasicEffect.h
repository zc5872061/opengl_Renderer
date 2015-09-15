//
//  BasicEffect.h
//  test
//
//  Created by Chukie on 15/9/12.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#pragma once
#include "Common.h"
#include "ShaderProgram.h"
#include "VertexDeclarations.h"
#include "Variable.h"

namespace Library {
    class BasicEffect:public ShaderProgram
    {
        SHADER_VARIABLE_DECLARATION(WorldViewProjection)
    public:
        BasicEffect();
        ~BasicEffect();
        virtual void Initialize(GLuint vertexArrayObject) override;
        void CreateVertexBuffer(VertexPositionColor* vertices, unsigned int vertexCount, GLuint& vertexBuffer) const;
        virtual unsigned int VertexSize() const;
    private:
        enum VertexAttribute
        {
            VertexAttributePosition = 0,
            VertexAttributeColor = 1
        };
    };
}
