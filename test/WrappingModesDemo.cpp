//
//  WrappingModesDemo.cpp
//  test
//
//  Created by Chukie on 15/9/16.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#include "SOIL.h"
#include "WrappingModesDemo.h"
#include "ColorHelper.h"
#include "Camera.h"

using namespace glm;

namespace Rendering {
    WrappingModesDemo::WrappingModesDemo(Game* game, Camera* camera):
    DrawableGameComponent(game,camera),
    mVertexArrayObject(0),
    mVertexBuffer(0),
    mIndexBuffer(0),
    mWorldViewProjectionLocation(-1),
    mWorldMatrix(),
    mIndexCount(0),
    mColorTexture(-1),
    mTextureSamplers(),
    mTextureSamplersByWrappingMode(),
    mActiveWrappingMode(WrappingModeMirroredRepeat)
    {
        mShaderProgram = new ShaderProgram();
    }
    
    WrappingModesDemo::~WrappingModesDemo()
    {
        glDeleteSamplers((int)mTextureSamplers.size(),&mTextureSamplers[0]);
        glDeleteTextures(1, &mColorTexture);
        glDeleteBuffers(1,&mVertexBuffer);
        glDeleteBuffers(1,&mIndexBuffer);
        glDeleteVertexArrays(1,&mVertexArrayObject);
        
    }
    
    void WrappingModesDemo::Initialize()
    {
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,WrappingVStr));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,WrappingFStr));
        mShaderProgram->BuildProgram(shaders);
        float size = 10.0f;
        float halfSize = size/2;
        
        // Create the vertex buffer
        VertexPositionTexture vertices[] =
        {
            VertexPositionTexture(vec4(-halfSize, 1.0f, 0.0, 1.0f), vec2(0.0f, 3.0f)),
            VertexPositionTexture(vec4(-halfSize, size + 1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
            VertexPositionTexture(vec4(halfSize, size + 1.0f, 0.0f, 1.0f), vec2(3.0f, 0.0f)),
            VertexPositionTexture(vec4(halfSize, 1.0f, 0.0f, 1.0f), vec2(3.0f, 3.0f))
        };
        
        CreateVertexBuffer(vertices, 4, mVertexBuffer);
        
        //create index buffer
        unsigned int indices[] =
        {
            0,2,1,
            0,3,2
        };
        
        mIndexBuffer = 6;
        CreateIndexBuffer(indices, mIndexCount, mIndexBuffer);
        
        
        // Find the WVP uniform location
        mWorldViewProjectionLocation = glGetUniformLocation(mShaderProgram->Program(), "WorldViewProjection");
        assert(mWorldViewProjectionLocation != -1);
        
        mColorTexture = SOIL_load_OGL_texture("/Users/chukie/Desktop/Demo/opengl_framework/test/resource/Cover.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB);
        assert(mColorTexture != 0);
        
        mTextureSamplers.resize(WrappingModeEnd);
        glGenSamplers(WrappingModeEnd,&mTextureSamplers[0]);
        
        for(WrappingMode mode = (WrappingMode)0; mode < WrappingModeEnd; mode = (WrappingMode)(mode+1))
        {
            mTextureSamplersByWrappingMode[mode] = mTextureSamplers[mode];
        }
        
        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeRepeat],GL_TEXTURE_WRAP_S,GL_REPEAT);
        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeRepeat],GL_TEXTURE_WRAP_T,GL_REPEAT);
        
        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeMirroredRepeat],GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeMirroredRepeat],GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);
        
        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeClampToEdge],GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeClampToEdge],GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        
        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeClampToBorder],GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeClampToBorder],GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
        glSamplerParameterfv(mTextureSamplersByWrappingMode[WrappingModeClampToBorder], GL_TEXTURE_BORDER_COLOR, &ColorHelper::Purple[0]);
        
        
        //create the vertex array object
        glGenVertexArrays(1,&mVertexArrayObject);
        glBindVertexArray(mVertexArrayObject);
        
        glVertexAttribPointer(VertexAttributePosition,4,GL_FLOAT,GL_FALSE,sizeof(VertexPositionTexture),(void*)offsetof(VertexPositionTexture, Position));
        glEnableVertexAttribArray(VertexAttributePosition);
        
        glVertexAttribPointer(VertexAttributeTextureCoordinate,2,GL_FLOAT,GL_FALSE,sizeof(VertexPositionTexture),(void*)offsetof(VertexPositionTexture, TextureCoordinates));
        glEnableVertexAttribArray(VertexAttributeTextureCoordinate);
        
        glBindVertexArray(0);
        
        
    }
    
    void WrappingModesDemo::Draw(GameTime gametime)
    {
        glBindVertexArray(mVertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER,mVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mIndexBuffer);
        glBindTexture(GL_TEXTURE_2D, mColorTexture);
        
        glBindSampler(0,mTextureSamplersByWrappingMode[mActiveWrappingMode]);
        glUseProgram(mShaderProgram->Program());
        mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
        glUniformMatrix4fv(mWorldViewProjectionLocation,1,GL_FALSE,&wvp[0][0]);
        
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        
        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
        
    }
    
    void WrappingModesDemo::CreateVertexBuffer(VertexPositionTexture* vertices, GLuint vertexCount, GLuint& vertexBuffer)
    {
        glGenBuffers(1,&mVertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER,mVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER,sizeof(VertexPositionTexture) * vertexCount,&vertices[0],GL_STATIC_DRAW);
    }
    
    void WrappingModesDemo::CreateIndexBuffer(unsigned int* indices, GLuint indexCount, GLuint& indexBuffer)
    {
        glGenBuffers(1,&indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int) * indexCount, indices,GL_STATIC_DRAW);
    }
}