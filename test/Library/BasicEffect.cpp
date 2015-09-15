//
//  BasicEffect.cpp
//  test
//
//  Created by Chukie on 15/9/12.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "BasicEffect.h"

using namespace Library;
using namespace::glm;

namespace Library {
    BasicEffect::BasicEffect():
    SHADER_VARIABLE_INITIALIZATION(WorldViewProjection)
    {
        
    }
    
    SHADER_VARIABLE_DEFINITION(BasicEffect,WorldViewProjection)
    
    BasicEffect::~BasicEffect()
    {
        
    }
    
    void BasicEffect::Initialize(GLuint vertexArrayObject)
    {
        ShaderProgram::Initialize(vertexArrayObject);
        SHADER_VARIABLE_INSTANTIATE(WorldViewProjection)
        
        glVertexAttribPointer(VertexAttributePosition, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), (void*)offsetof(VertexPositionColor, Position));
        glEnableVertexAttribArray(VertexAttributePosition);
        
        glVertexAttribPointer(VertexAttributeColor, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), (void*)offsetof(VertexPositionColor, Color));
        glEnableVertexAttribArray(VertexAttributeColor);
    }
    
    
    void BasicEffect::CreateVertexBuffer(VertexPositionColor* vertices, unsigned int vertexCount, GLuint& vertexBuffer) const
    {
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, VertexSize() * vertexCount, &vertices[0], GL_STATIC_DRAW);
    }
    
    unsigned int BasicEffect::VertexSize() const
    {
        return sizeof(VertexPositionColor);
    }
}