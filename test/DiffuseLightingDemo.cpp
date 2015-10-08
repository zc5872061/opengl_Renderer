//
//  DiffuseLightingDemo.cpp
//  test
//
//  Created by Chukie on 15/9/28.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "DiffuseLightingDemo.h"
#include "SOIL.h"
#include "VertexDeclarations.h"
#include "ColorHelper.h"
#include "Game.h"
#include "Camera.h"
#include "VectorHelper.h"
#include <glm/glm/gtx/transform.hpp>

using namespace glm;

namespace Library {
    
    const vec2 DiffuseLightingDemo::LightRotationRate = vec2(360.0f, 360.0f);
    
    DiffuseLightingDemo::DiffuseLightingDemo(Game* game,Camera* camera):
    DrawableGameComponent(game,camera),
    mShaderProgram(),
    mVertexArrayObject(0),
    mVertexBuffer(0),
    mIndexBuffer(0),
    mWorldViewProjectionLocation(-1),
    mWorldLocation(-1),
    mAmbientColorLocation(-1),
    mLightColorLocation(-1),
    mLightDirectionLocation(-1),
    mWorldMatrix(),
    mIndexCount(0),
    mColorTexture(0),
    mAmbientLight(nullptr),
    mDirectionLight(nullptr),
    mModel(nullptr)
    {
        
    }
    
    DiffuseLightingDemo::~DiffuseLightingDemo()
    {

        DeleteObject(mAmbientLight)
        DeleteObject(mDirectionLight)
        
        glDeleteTextures(1, &mColorTexture);
        glDeleteBuffers(1,&mVertexBuffer);
        glDeleteBuffers(1,&mIndexBuffer);
        glDeleteVertexArrays(1,&mVertexArrayObject);
    }
    
    void DiffuseLightingDemo::Initialize()
    {
        // Build the shader program
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,DiffuseLightingVStr));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,DiffuseLightingFStr));
        mShaderProgram.BuildProgram(shaders);
        
        mModel = new Model(dragonModel,true);
        Mesh* mesh = mModel->Meshes().at(0);
        CreateVertexBuffer(*mesh, mVertexBuffer);
        mesh->CreateIndexBuffer(mIndexBuffer);
        mIndexCount = mesh->Indices().size();
        
        mWorldViewProjectionLocation = glGetUniformLocation(mShaderProgram.Program(), "WorldViewProjection");
        assert(mWorldViewProjectionLocation != -1);
        
        mWorldLocation = glGetUniformLocation(mShaderProgram.Program(), "World");
        assert(mWorldLocation != -1);
        
        mAmbientColorLocation = glGetUniformLocation(mShaderProgram.Program(), "AmbientColor");
        assert(mAmbientColorLocation != -1);
        
        mLightColorLocation = glGetUniformLocation(mShaderProgram.Program(), "LightColor");
        assert(mLightColorLocation != -1);
        
        mLightDirectionLocation = glGetUniformLocation(mShaderProgram.Program(), "LightDirection");
        assert(mLightDirectionLocation != -1);
        
        // Load the texture
        mColorTexture = SOIL_load_OGL_texture(earthImgStr, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
        assert(mColorTexture != 0);
        
        // Create the vertex array object
        glGenVertexArrays(1, &mVertexArrayObject);
        glBindVertexArray(mVertexArrayObject);
        
        glVertexAttribPointer(VertexAttributePosition, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTextureNormal), (void*)offsetof(VertexPositionTextureNormal, Position));
        glEnableVertexAttribArray(VertexAttributePosition);
        
        glVertexAttribPointer(VertexAttributeTextureCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTextureNormal), (void*)offsetof(VertexPositionTextureNormal, TextureCoordinates));
        glEnableVertexAttribArray(VertexAttributeTextureCoordinate);
        
        glVertexAttribPointer(VertexAttributeNormal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTextureNormal), (void*)offsetof(VertexPositionTextureNormal, Normal));
        glEnableVertexAttribArray(VertexAttributeNormal);
        
        glBindVertexArray(0);
        
        mAmbientLight = new Light(mGame);
        mAmbientLight->SetColor(ColorHelper::Black);
        
        mDirectionLight = new DirectionLight(mGame);
    }
    
    void DiffuseLightingDemo::Update(GameTime gametime)
    {
        UpdateAmbientLight(gametime);
        UpdateDirectionalLight(gametime);
    }
    
    void DiffuseLightingDemo::Draw(GameTime gametime)
    {
        glBindVertexArray(mVertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mIndexBuffer);
        
        glUseProgram(mShaderProgram.Program());
        mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
        glUniformMatrix4fv(mWorldViewProjectionLocation,1,GL_FALSE,&wvp[0][0]);
        glUniformMatrix4fv(mWorldLocation,1,GL_FALSE,&mWorldMatrix[0][0]);
        glUniform4fv(mAmbientColorLocation, 1, &mAmbientLight->Color()[0]);
        glUniform4fv(mLightColorLocation, 1, &mDirectionLight->Color()[0]);
        glUniform3fv(mLightDirectionLocation, 1, &mDirectionLight->Direction()[0]);
        
        glBindTexture(GL_TEXTURE_2D, mColorTexture);
        
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    
    void DiffuseLightingDemo::CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer)
    {
        const std::vector<vec3>& sourceVertices = mesh.Vertices();
        std::vector<VertexPositionTextureNormal> vertices;
        vertices.reserve(sourceVertices.size());
        
        //std::vector<vec3>* textureCoordinates = mesh.TextureCoordinates().at(0);
        //assert(textureCoordinates->size() == sourceVertices.size());
        
        const std::vector<vec3>& normals = mesh.Normals();
        assert(normals.size() == sourceVertices.size());
        
        for(unsigned int i = 0; i < sourceVertices.size(); i++)
        {
            vec3 position = sourceVertices.at(i);
            vec2 uv = vec2(0.0);
            vec3 normal = normals.at(i);
            vertices.push_back(VertexPositionTextureNormal(vec4(position.x, position.y, position.z, 1.0f), uv, normal));
        }
        
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionTextureNormal) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    }
    
    void DiffuseLightingDemo::UpdateAmbientLight(const GameTime& gameTime)
    {
        static float ambientIntensity = 0.0f;
        if (glfwGetKey(mGame->Window(), GLFW_KEY_PAGE_UP) && ambientIntensity < 1.0f)
        {
            ambientIntensity += (float)gameTime.ElapsedGameTime();
            ambientIntensity = glm::min(ambientIntensity, 1.0f);
        }
        
        if (glfwGetKey(mGame->Window(), GLFW_KEY_PAGE_DOWN) && ambientIntensity > 0.0f)
        {
            ambientIntensity -= (float)gameTime.ElapsedGameTime();
            ambientIntensity = glm::max(ambientIntensity, 0.0f);
            
            mAmbientLight->SetColor(vec4((vec3)ambientIntensity, 1.0f));
        }
    }
    
    void DiffuseLightingDemo::UpdateDirectionalLight(const GameTime& gameTime)
    {
        static float directionalIntensity = 1.0f;
        float elapsedTime = (float)gameTime.ElapsedGameTime();
        
        // Upddate directional light intensity
        if (glfwGetKey(mGame->Window(), GLFW_KEY_HOME) && directionalIntensity < 1.0f)
        {
            directionalIntensity += elapsedTime;
            directionalIntensity = glm::min(directionalIntensity, 1.0f);
            
            mDirectionLight->SetColor(vec4((vec3)directionalIntensity, 1.0f));
        }
        if (glfwGetKey(mGame->Window(), GLFW_KEY_END) && directionalIntensity > 0.0f)
        {
            directionalIntensity -= elapsedTime;
            directionalIntensity = glm::max(directionalIntensity, 0.0f);
            
            mDirectionLight->SetColor(vec4((vec3)directionalIntensity, 1.0f));
        }
        
        // Rotate directional light
        vec2 rotationAmount = Vector2Helper::Zero;
        if (glfwGetKey(mGame->Window(), GLFW_KEY_LEFT))
        {
            rotationAmount.x += LightRotationRate.x * elapsedTime;
        }
        if (glfwGetKey(mGame->Window(), GLFW_KEY_RIGHT))
        {
            rotationAmount.x -= LightRotationRate.x * elapsedTime;
        }
        if (glfwGetKey(mGame->Window(), GLFW_KEY_UP))
        {
            rotationAmount.y += LightRotationRate.y * elapsedTime;
        }
        if (glfwGetKey(mGame->Window(), GLFW_KEY_DOWN))
        {
            rotationAmount.y -= LightRotationRate.y * elapsedTime;
        }
        
        mat4 lightRotationMatrix;
        if (rotationAmount.x != 0)
        {
            lightRotationMatrix = glm::rotate(mat4(), rotationAmount.x, Vector3Helper::Up);
        }
        
        if (rotationAmount.y != 0)
        {
            lightRotationMatrix = glm::rotate(lightRotationMatrix, rotationAmount.y, mDirectionLight->Right());
        }
        
        if (rotationAmount.x != 0.0f || rotationAmount.y != 0.0f)
        {
            mDirectionLight->ApplyRotation(lightRotationMatrix);
        }
    }
    
}
