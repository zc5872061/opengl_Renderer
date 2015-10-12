//
//  BillboardEffect.cpp
//  OglRenderer
//
//  Created by Chukie on 15/10/12.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "BillboardEffect.h"

namespace Library {
    BillboardEffect::BillboardEffect():
    SHADER_VARIABLE_INITIALIZATION(gVP),
    SHADER_VARIABLE_INITIALIZATION(gCameraPos)
    {
       
    }
    
    SHADER_VARIABLE_DEFINITION(BillboardEffect, gVP)
    SHADER_VARIABLE_DEFINITION(BillboardEffect, gCameraPos)
    
    void BillboardEffect::Initialize(GLuint vertexArrayObject)
    {
        ShaderProgram::Initialize(vertexArrayObject);
        SHADER_VARIABLE_INSTANTIATE(gVP)
        SHADER_VARIABLE_INSTANTIATE(gCameraPos)
    }
    
    void BillboardEffect::createVertexBuffer(Mesh& mesh, GLuint& vertexBuffer)const
    {
        
    }
    
    void BillboardEffect::CreateVertexBuffer(VertexPosition* vertices, unsigned int vertexCount, GLuint& vertexBuffer) const
    {
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, VertexSize() * vertexCount, &vertices[0], GL_STATIC_DRAW);
    }
    
    unsigned int BillboardEffect::VertexSize() const
    {
         return sizeof(VertexPositionColor);
    }
}