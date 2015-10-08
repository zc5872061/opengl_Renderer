//
//  BlinnPhongEffect.h
//  test
//
//  Created by Chukie on 15/10/2.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Common.h"
#include "ShaderProgram.h"
#include "VertexDeclarations.h"
#include "Mesh.h"


namespace Library {
    class BlinnPhongEffect:public ShaderProgram
    {
        SHADER_VARIABLE_DECLARATION(WorldViewProjection)
        SHADER_VARIABLE_DECLARATION(World)
        SHADER_VARIABLE_DECLARATION(AmbientColor)
        SHADER_VARIABLE_DECLARATION(LightColor)
        SHADER_VARIABLE_DECLARATION(LightDirection)
        SHADER_VARIABLE_DECLARATION(CameraPosition)
        SHADER_VARIABLE_DECLARATION(SpecularColor)
        SHADER_VARIABLE_DECLARATION(SpecularPower)
    public:
        BlinnPhongEffect();
        ~BlinnPhongEffect();
        
        virtual void Initialize(GLuint vertexArrayObject) override;
        void createVertexBuffer(Mesh& mesh, GLuint& vertexBuffer) const;
        void CreateVertexBuffer(VertexPositionTextureNormal* vertices, unsigned int vertexCount, GLuint& vertexBuffer) const;
        virtual unsigned int VertexSize() const;
    private:
        enum VertexAttribute
        {
            VertexAttributePosition = 0,
            VertexAttributeTextureCoordinate = 1,
            VertexAttributeNormal = 2
        };
    };
}