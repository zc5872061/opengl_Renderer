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

using namespace glm;

namespace Library {
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
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,""));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,""));
        mShaderProgram.BuildProgram(shaders);
        
        mModel = new Model("",true);
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
        mColorTexture = SOIL_load_OGL_texture("Content\\Textures\\EarthComposite.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
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
        
    }
    
    void DiffuseLightingDemo::Draw(GameTime gametime)
    {
        
    }
    
    void DiffuseLightingDemo::CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer)
    {
        const std::vector<vec3>& sourceVertices = mesh.Vertices();
        std::vector<VertexPositionTextureNormal> vertices;
        vertices.reserve(sourceVertices.size());
        
        std::vector<vec3>* textureCoordinates = mesh.TextureCoordinates().at(0);
        assert(textureCoordinates->size() == sourceVertices.size());
        
        const std::vector<vec3>& normals = mesh.Normals();
        assert(normals.size() == sourceVertices.size());
        
        for(unsigned int i = 0; i < sourceVertices.size(); i++)
        {
            vec3 position = sourceVertices.at(i);
            vec2 uv = (vec2)textureCoordinates->at(i);
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
        
    }
}
