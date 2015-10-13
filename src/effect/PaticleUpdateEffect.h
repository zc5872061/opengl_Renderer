//
//  PaticleUpdateEffect
//  OglRenderer
//
//  Created by Chukie on 15/10/13.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once
#include "Common.h"
#include "ShaderProgram.h"
#include "VertexDeclarations.h"
#include "Mesh.h"


namespace Library {
    class PaticleUpdateEffect:public ShaderProgram
    {
        SHADER_VARIABLE_DECLARATION(gDeltaTimeMillis)
        SHADER_VARIABLE_DECLARATION(gRandomTexture)
        SHADER_VARIABLE_DECLARATION(gTime)
        SHADER_VARIABLE_DECLARATION(gLauncherLifetime)
        SHADER_VARIABLE_DECLARATION(gShellLifetime)
        SHADER_VARIABLE_DECLARATION(gSecondaryShellLifetime)
    public:
        PaticleUpdateEffect();
        virtual void Initialize(GLuint vertexArrayObject) override;
        void createVertexBuffer(Mesh& mesh, GLuint& vertexBuffer) const;
        void CreateVertexBuffer(VertexPaticle* vertices, unsigned int vertexCount, GLuint& vertexBuffer) const;
        virtual unsigned int VertexSize() const;
    private:
        enum VertexAttribute
        {
            VertexAttributePosition = 0,
            VertexAttributeColor = 1
        };

    };
}
