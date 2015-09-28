//
//  AmbientLightingDemo.cpp
//  test
//
//  Created by Chukie on 15/9/28.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "AmbientLightingDemo.h"
#include "VertexDeclarations.h"
#include "Camera.h"
#include "Util.h"
#include "SOIL.h"
#include "Game.h"


namespace Library {
    AmbientLightingDemo::AmbientLightingDemo(Game* game,Camera* camera):
        DrawableGameComponent(game,camera),
        mShaderProgram(),
        mVertexArrayObject(0),
        mVertexBuffer(0),
        mIndexBuffer(0),
        mWorldViewProjectionLocation(-1),
        mAmbientColorLocation(-1),
        mWorldMatrix(),
        mIndexCount(0),
        mColorTexture(0),
        mAmbientLight(nullptr),
        mModel(nullptr)
    {
        
    }
    
    AmbientLightingDemo::~AmbientLightingDemo()
    {
        if(mAmbientLight != nullptr)
        {
            delete mAmbientLight;
            mAmbientLight = nullptr;
        }
        
        glDeleteTextures(1, &mColorTexture);
        glDeleteBuffers(1,&mIndexBuffer);
        glDeleteBuffers(1,&mVertexBuffer);
        glDeleteVertexArrays(1,&mVertexArrayObject);
    }

    void AmbientLightingDemo::Initialize()
    {
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,AmbientLightVStr));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,AmbientLightFStr));
        mShaderProgram.BuildProgram(shaders);
        mModel = new Model(sphereModel,true);
        Mesh* mesh = mModel->Meshes().at(0);
        CreateVertexBuffer(*mesh, mVertexBuffer);
        mesh->CreateIndexBuffer(mIndexBuffer);
        mIndexCount = mesh->Indices().size();
        mWorldViewProjectionLocation = glGetUniformLocation(mShaderProgram.Program(), "WorldViewProjection");
        assert(mWorldViewProjectionLocation != -1);
        mAmbientColorLocation = glGetUniformLocation(mShaderProgram.Program(), "AmbientColor");
        assert(mAmbientColorLocation != -1);
        mColorTexture = SOIL_load_OGL_texture(earthImgStr,SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
        assert(mColorTexture != 0);
        
        // Create vertex array object
        glGenVertexArrays(1, &mVertexArrayObject);
        glBindVertexArray(mVertexArrayObject);
        
        glVertexAttribPointer(VertexAttributePosition, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTexture), (void*)offsetof(VertexPositionTexture, Position));
        glEnableVertexAttribArray(VertexAttributePosition);
        
        glVertexAttribPointer(VertexAttributeTextureCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTexture), (void*)offsetof(VertexPositionTexture, TextureCoordinates));
        glEnableVertexAttribArray(VertexAttributeTextureCoordinate);
        mAmbientLight = new Light(mGame);
    }
    
    void AmbientLightingDemo::Update(GameTime gametime)
    {
        UpdateAmbientLight(gametime);
    }
    
    void AmbientLightingDemo::Draw(GameTime gametime)
    {
        glBindVertexArray(mVertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
        
        glUseProgram(mShaderProgram.Program());
        
        mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
        glUniformMatrix4fv(mWorldViewProjectionLocation, 1, GL_FALSE, &wvp[0][0]);
        glUniform4fv(mAmbientColorLocation, 1, &mAmbientLight->Color()[0]);
        
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glEnable(GL_ALPHA_TEST); 
        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
    }
    
    void AmbientLightingDemo::CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer)
    {
        const std::vector<vec3>& sourceVertices = mesh.Vertices();
        
        std::vector<VertexPositionTexture> vertices;
        vertices.reserve(sourceVertices.size());
        
        std::vector<vec3>* textureCoordinates = mesh.TextureCoordinates().at(0);
        assert(textureCoordinates->size() == sourceVertices.size());
        
        for(int i = 0; i < sourceVertices.size(); i++)
        {
            vec3 position = sourceVertices.at(i);
            vec2 uv = (vec2)textureCoordinates->at(i);
            vertices.push_back(VertexPositionTexture(vec4(position.x, position.y, position.z, 1.0f), uv));
        }
        
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionTexture) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    }
    
    void AmbientLightingDemo::UpdateAmbientLight(const GameTime& gameTime)
    {
        static float ambientIntensity = 1.0f;
        
        if (glfwGetKey(mGame->Window(), GLFW_KEY_PAGE_UP) && ambientIntensity < 1.0f)
        {
            ambientIntensity += (float)gameTime.ElapsedGameTime();
            ambientIntensity = glm::min(ambientIntensity, 1.0f);
            
            mAmbientLight->SetColor(vec4((vec3)ambientIntensity, 1.0f));
        }
        
        if (glfwGetKey(mGame->Window(), GLFW_KEY_PAGE_DOWN) && ambientIntensity > 0.0f)
        {
            ambientIntensity -= (float)gameTime.ElapsedGameTime();
            ambientIntensity = glm::max(ambientIntensity, 0.0f);
            
            mAmbientLight->SetColor(vec4((vec3)ambientIntensity, 1.0f));
        }
    }
}