//
//  PaticleSystem.cpp
//  OglRenderer
//
//  Created by Chukie on 15/10/13.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "PaticleUpdateEffect.h"

namespace Library {
    PaticleUpdateEffect::PaticleUpdateEffect():
    SHADER_VARIABLE_INITIALIZATION(gDeltaTimeMillis),
    SHADER_VARIABLE_INITIALIZATION(gRandomTexture),
    SHADER_VARIABLE_INITIALIZATION(gTime),
    SHADER_VARIABLE_INITIALIZATION(gLauncherLifetime),
    SHADER_VARIABLE_INITIALIZATION(gShellLifetime),
    SHADER_VARIABLE_INITIALIZATION(gSecondaryShellLifetime)
    {
        
    }
    
    SHADER_VARIABLE_DEFINITION(PaticleUpdateEffect, gDeltaTimeMillis)
    SHADER_VARIABLE_DEFINITION(PaticleUpdateEffect, gRandomTexture)
    SHADER_VARIABLE_DEFINITION(PaticleUpdateEffect, gTime)
    SHADER_VARIABLE_DEFINITION(PaticleUpdateEffect, gLauncherLifetime)
    SHADER_VARIABLE_DEFINITION(PaticleUpdateEffect, gShellLifetime)
    SHADER_VARIABLE_DEFINITION(PaticleUpdateEffect, gSecondaryShellLifetime)
    
    void PaticleUpdateEffect::Initialize(GLuint vertexArrayObject)
    {
        ShaderProgram::Initialize(vertexArrayObject);
        
        SHADER_VARIABLE_INSTANTIATE(gDeltaTimeMillis)
        SHADER_VARIABLE_INSTANTIATE(gTime)
        SHADER_VARIABLE_INSTANTIATE(gRandomTexture)
        
        SHADER_VARIABLE_INSTANTIATE(gLauncherLifetime)
        SHADER_VARIABLE_INSTANTIATE(gShellLifetime)
        SHADER_VARIABLE_INSTANTIATE(gSecondaryShellLifetime)
    }
    
    void PaticleUpdateEffect::createVertexBuffer(Mesh& mesh, GLuint& vertexBuffer) const
    {
        
    }
    
    void PaticleUpdateEffect::CreateVertexBuffer(VertexPaticle* vertices, unsigned int vertexCount, GLuint& vertexBuffer) const
    {
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, VertexSize() * vertexCount, &vertices[0], GL_STATIC_DRAW);
    }
    
    unsigned int PaticleUpdateEffect::VertexSize() const
    {
        return sizeof(VertexPaticle);
    }
}