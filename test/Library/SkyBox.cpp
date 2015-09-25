//
//  SkyBox.cpp
//  test
//
//  Created by Chukie on 15/9/25.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "SkyBox.h"
#include <glm/glm/gtc/matrix_transform.inl>
#include "SOIL.h"
#include "Camera.h"

using namespace Library;
using namespace glm;

namespace Library {
    SkyBox::SkyBox(
                   Game* game,
                   Camera* camera,
                   const std::string& posXFilename,
                   const std::string& negXFilename,
                   const std::string& posYFilename,
                   const std::string& negYFilename,
                   const std::string& posZFilename,
                   const std::string& negZFilename,
                   float mscale
                   ):
        DrawableGameComponent(game,camera),
        mModel(nullptr),
        mPosXFilename(posXFilename),
        mNegXFilename(negXFilename),
        mPosYFilename(posYFilename),
        mNegYFilename(negYFilename),
        mPosZFilename(posZFilename),
        mNegZFilename(negZFilename)
    {
        mScaleMatrix = scale(mat4(),vec3(.5));
    }
    
    SkyBox::~SkyBox()
    {
        glDeleteSamplers(1, &mSkyboxTextureSampler);
        glDeleteTextures(1,&mSkyboxTexture);
        glDeleteBuffers(1, &mIndexBuffer);
        glDeleteBuffers(1, &mVertexBuffer);
        glDeleteVertexArrays(1, &mVertexArrayObject);
    }
    
    void SkyBox::Initialize()
    {
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,SkyBoxVStr));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,SkyBoxFStr));
        mShaderProgram.BuildProgram(shaders);
        
        mModel = new Model(sphereModel,true);
        // Create the vertex and index buffers
        Mesh* mesh = mModel->Meshes().at(0);
        mShaderProgram.createVertexBuffer(*mesh, mVertexBuffer);
        mesh->CreateIndexBuffer(mIndexBuffer);
        mIndexCount = mesh->Indices().size();
        mSkyboxTexture = SOIL_load_OGL_cubemap(mPosXFilename.c_str(),
                                               mNegXFilename.c_str(),
                                               mPosYFilename.c_str(),
                                               mNegYFilename.c_str(),
                                               mPosZFilename.c_str(),
                                               mNegZFilename.c_str(),
                                               SOIL_LOAD_AUTO,
                                               SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                                               );
        assert(mSkyboxTexture != 0);
        
        glGenSamplers(1, &mSkyboxTextureSampler);
        glSamplerParameteri(mSkyboxTextureSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glSamplerParameteri(mSkyboxTextureSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glSamplerParameteri(mSkyboxTextureSampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(mSkyboxTextureSampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(mSkyboxTextureSampler, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        
        // Create the vertex array object
        glGenVertexArrays(1, &mVertexArrayObject);
        mShaderProgram.Initialize(mVertexArrayObject);
    }
    
    void SkyBox::Update(GameTime gametime)
    {
        //mWorldMatrix = translate(mat4(), mCamera->Position()) * mScaleMatrix;
        mWorldMatrix = translate(mat4(), vec3(1.0)) * mScaleMatrix;
    }
    
    void SkyBox::Draw(GameTime gametime)
    {
        glBindVertexArray(mVertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
        glBindSampler(0, mSkyboxTextureSampler);
        
        mShaderProgram.Use();
        
        mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
        *(mShaderProgram.WorldViewProjection()) << wvp;
        
        glBindTexture(GL_TEXTURE_CUBE_MAP, mSkyboxTexture);
        
        glDisable(GL_CULL_FACE);
        
        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
    }
}