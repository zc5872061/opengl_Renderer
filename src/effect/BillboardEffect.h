//
//  BillboardEffect.h
//  OglRenderer
//
//  Created by Chukie on 15/10/12.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#pragma once
#include "Common.h"
#include "ShaderProgram.h"
#include "VertexDeclarations.h"
#include "Mesh.h"


namespace Library {
    class BillboardEffect:public ShaderProgram
    {
        SHADER_VARIABLE_DECLARATION(gVP)
        SHADER_VARIABLE_DECLARATION(gCameraPos)
    public:
        BillboardEffect();
        virtual void Initialize(GLuint vertexArrayObject) override;
        void createVertexBuffer(Mesh& mesh, GLuint& vertexBuffer) const;
        void CreateVertexBuffer(VertexPosition* vertices, unsigned int vertexCount, GLuint& vertexBuffer) const;
        virtual unsigned int VertexSize() const;
    private:
        enum VertexAttribute
        {
            VertexAttributePosition = 0,
            VertexAttributeColor = 1
        };

    };
}