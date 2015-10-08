//
//  BlinnPhongEffect.cpp
//  test
//
//  Created by Chukie on 15/10/2.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "BlinnPhongEffect.h"

using namespace glm;

namespace Library {
    BlinnPhongEffect::BlinnPhongEffect():
    SHADER_VARIABLE_INITIALIZATION(WorldViewProjection),
    SHADER_VARIABLE_INITIALIZATION(World),
    SHADER_VARIABLE_INITIALIZATION(AmbientColor),
    SHADER_VARIABLE_INITIALIZATION(LightColor),
    SHADER_VARIABLE_INITIALIZATION(LightDirection),
    SHADER_VARIABLE_INITIALIZATION(CameraPosition),
    SHADER_VARIABLE_INITIALIZATION(SpecularColor),
    SHADER_VARIABLE_INITIALIZATION(SpecularPower)
    {
        
    }
    
    SHADER_VARIABLE_DEFINITION(BlinnPhongEffect, WorldViewProjection)
    SHADER_VARIABLE_DEFINITION(BlinnPhongEffect, World)
    SHADER_VARIABLE_DEFINITION(BlinnPhongEffect, AmbientColor)
    SHADER_VARIABLE_DEFINITION(BlinnPhongEffect, LightColor)
    SHADER_VARIABLE_DEFINITION(BlinnPhongEffect, LightDirection)
    SHADER_VARIABLE_DEFINITION(BlinnPhongEffect, CameraPosition)
    SHADER_VARIABLE_DEFINITION(BlinnPhongEffect, SpecularColor)
    SHADER_VARIABLE_DEFINITION(BlinnPhongEffect, SpecularPower)
    
    BlinnPhongEffect::~BlinnPhongEffect()
    {
        
    }
    
    void BlinnPhongEffect::Initialize(GLuint vertexArrayObject)
    {
        ShaderProgram::Initialize(vertexArrayObject);
        SHADER_VARIABLE_INSTANTIATE(WorldViewProjection)
        SHADER_VARIABLE_INSTANTIATE(World)
        SHADER_VARIABLE_INSTANTIATE(AmbientColor)
        SHADER_VARIABLE_INSTANTIATE(LightColor)
        SHADER_VARIABLE_INSTANTIATE(LightDirection)
        SHADER_VARIABLE_INSTANTIATE(CameraPosition)
        SHADER_VARIABLE_INSTANTIATE(SpecularColor)
        SHADER_VARIABLE_INSTANTIATE(SpecularPower)
        
        glVertexAttribPointer(VertexAttributePosition, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTextureNormal), (void*)offsetof(VertexPositionTextureNormal, Position));
        glEnableVertexAttribArray(VertexAttributePosition);
        
        glVertexAttribPointer(VertexAttributeTextureCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTextureNormal), (void*)offsetof(VertexPositionTextureNormal, TextureCoordinates));
        glEnableVertexAttribArray(VertexAttributeTextureCoordinate);
        
        glVertexAttribPointer(VertexAttributeNormal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTextureNormal), (void*)offsetof(VertexPositionTextureNormal, Normal));
        glEnableVertexAttribArray(VertexAttributeNormal);
    }
    
    void BlinnPhongEffect::createVertexBuffer(Mesh& mesh, GLuint& vertexBuffer) const
    {
        const std::vector<vec3>& sourceVertices = mesh.Vertices();
        
        std::vector<VertexPositionTextureNormal> vertices;
        vertices.reserve(sourceVertices.size());
        
        //std::vector<vec3>* textureCoordinates = mesh.TextureCoordinates().at(0);
        //assert(textureCoordinates->size() == sourceVertices.size());
        
        const std::vector<vec3>& normals = mesh.Normals();
        assert(normals.size() == sourceVertices.size());
        
        for (UINT i = 0; i < sourceVertices.size(); i++)
        {
            vec3 position = sourceVertices.at(i);
            //vec2 uv = (vec2)textureCoordinates->at(i);
            vec2 uv = vec2(0.0);
            vec3 normal = normals.at(i);
            vertices.push_back(VertexPositionTextureNormal(vec4(position.x, position.y, position.z, 1.0f), uv, normal));
        }
        
        CreateVertexBuffer(&vertices[0], vertices.size(), vertexBuffer);
    }
    
    void BlinnPhongEffect::CreateVertexBuffer(VertexPositionTextureNormal* vertices, unsigned int vertexCount, GLuint& vertexBuffer) const
    {
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, VertexSize() * vertexCount, &vertices[0], GL_STATIC_DRAW);
    }
    
    unsigned int BlinnPhongEffect::VertexSize() const
    {
        return sizeof(VertexPositionTextureNormal);
    }
}