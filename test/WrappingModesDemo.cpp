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
        if(mShaderProgram)
        {
            delete mShaderProgram;
            mShaderProgram = nullptr;
        }
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
        float size = 2.0f;
        float halfSize = size/2;
        
        // Create the vertex buffer
        VertexPositionTexture vertices[] =
        {
            VertexPositionTexture(vec4(-halfSize+5, 0.0f,         0.0, 1.0f), vec2(0.0f,1.0f)),
            VertexPositionTexture(vec4(-halfSize+5, size + 0.0f,  0.0f, 1.0f), vec2(0.0f, 0.0f)),
            VertexPositionTexture(vec4(halfSize+5,  size + 0.0f,  0.0f, 1.0f), vec2(1.0f, 0.0f)),
            VertexPositionTexture(vec4(halfSize+5,  0.0f,         0.0f, 1.0f), vec2(1.0f, 1.0f))
        };
        
        CreateVertexBuffer(vertices, 4, mVertexBuffer);
        
        //create index buffer
        unsigned int indices[] =
        {
            0,2,1,
            0,3,2
        };
        
        mIndexCount = 6;
        CreateIndexBuffer(indices, 6, mIndexBuffer);
        
        
        // Find the WVP uniform location
        mWorldViewProjectionLocation = glGetUniformLocation(mShaderProgram->Program(), "WorldViewProjection");
        assert(mWorldViewProjectionLocation != -1);
        
        mColorTexture = loadBMP_custom("/Users/chukie/Desktop/Demo/opengl_framework/test/resource/uvtemplate.bmp");
        //mColorTexture = SOIL_load_OGL_texture(imgStr, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB );
        assert(mColorTexture != 0);
        
//        mTextureSamplers.resize(WrappingModeEnd);
//        glGenSamplers(WrappingModeEnd,&mTextureSamplers[0]);
//        
//        for(WrappingMode mode = (WrappingMode)0; mode < WrappingModeEnd; mode = (WrappingMode)(mode+1))
//        {
//            mTextureSamplersByWrappingMode[mode] = mTextureSamplers[mode];
//        }
//        
//        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeRepeat],GL_TEXTURE_WRAP_S,GL_REPEAT);
//        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeRepeat],GL_TEXTURE_WRAP_T,GL_REPEAT);
//        
//        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeMirroredRepeat],GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
//        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeMirroredRepeat],GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);
//        
//        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeClampToEdge],GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
//        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeClampToEdge],GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
//        
//        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeClampToBorder],GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
//        glSamplerParameteri(mTextureSamplersByWrappingMode[WrappingModeClampToBorder],GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
//        glSamplerParameterfv(mTextureSamplersByWrappingMode[WrappingModeClampToBorder], GL_TEXTURE_BORDER_COLOR, &ColorHelper::Purple[0]);
        
        
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
//        glBindVertexArray(mVertexArrayObject);
//        glBindBuffer(GL_ARRAY_BUFFER,mVertexBuffer);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mIndexBuffer);
//        glBindTexture(GL_TEXTURE_2D, mColorTexture);
//        
//        //glBindSampler(0,mTextureSamplersByWrappingMode[mActiveWrappingMode]);
//        glUseProgram(mShaderProgram->Program());
//        mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
//        glUniformMatrix4fv(mWorldViewProjectionLocation,1,GL_FALSE,&wvp[0][0]);
//        
//        glEnable(GL_CULL_FACE);
//        glFrontFace(GL_CCW);
//        
//        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT,0);
//        glBindVertexArray(0);
        
        glBindVertexArray(mVertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
        glBindTexture(GL_TEXTURE_2D, mColorTexture);
        //int w;
        //glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
        //glBindSampler(0, mTextureSamplersByWrappingMode[mActiveWrappingMode]);
        
        glUseProgram(mShaderProgram->Program());
        
        mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
        glUniformMatrix4fv(mWorldViewProjectionLocation, 1, GL_FALSE, &wvp[0][0]);
        
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        
        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
    }
    
    void WrappingModesDemo::CreateVertexBuffer(VertexPositionTexture* vertices, GLuint vertexCount, GLuint& vertexBuffer)
    {
        glGenBuffers(1,&vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER,sizeof(VertexPositionTexture) * vertexCount,vertices,GL_STATIC_DRAW);
        
        //glGenBuffers(1, &vertexBuffer);
        //glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionTexture) * vertexCount, &vertices[0], GL_STATIC_DRAW);
    }
    
    void WrappingModesDemo::CreateIndexBuffer(unsigned int* indices, GLuint indexCount, GLuint& indexBuffer)
    {
        glGenBuffers(1,&indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int) * indexCount, indices,GL_STATIC_DRAW);
        
//        glGenBuffers(1, &indexBuffer);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UINT) * indexCount, indices, GL_STATIC_DRAW);
    }
    
    GLuint WrappingModesDemo::loadBMP_custom(const char * imagepath)
    {
        printf("Reading image %s\n", imagepath);
        
        // Data read from the header of the BMP file
        unsigned char header[54];
        unsigned int dataPos;
        unsigned int imageSize;
        unsigned int width, height;
        // Actual RGB data
        unsigned char * data;
        
        // Open the file
        FILE * file = fopen(imagepath,"rb");
        if (!file)							    {printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar(); return 0;}
        
        // Read the header, i.e. the 54 first bytes
        
        // If less than 54 bytes are read, problem
        if ( fread(header, 1, 54, file)!=54 ){
            printf("Not a correct BMP file\n");
            return 0;
        }
        // A BMP files always begins with "BM"
        if ( header[0]!='B' || header[1]!='M' ){
            printf("Not a correct BMP file\n");
            return 0;
        }
        // Make sure this is a 24bpp file
        if ( *(int*)&(header[0x1E])!=0  )         {printf("Not a correct BMP file\n");    return 0;}
        if ( *(int*)&(header[0x1C])!=24 )         {printf("Not a correct BMP file\n");    return 0;}
        
        // Read the information about the image
        dataPos    = *(int*)&(header[0x0A]);
        imageSize  = *(int*)&(header[0x22]);
        width      = *(int*)&(header[0x12]);
        height     = *(int*)&(header[0x16]);
        
        // Some BMP files are misformatted, guess missing information
        if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
        if (dataPos==0)      dataPos=54; // The BMP header is done that way
        
        // Create a buffer
        data = new unsigned char [imageSize];
        
        // Read the actual data from the file into the buffer
        fread(data,1,imageSize,file);
        
        // Everything is in memory now, the file wan be closed
        fclose (file);
        
        // Create one OpenGL texture
        GLuint textureID;
        glGenTextures(1, &textureID);
        
        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        // Give the image to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
        
        // OpenGL has now copied the data. Free our own version
        delete [] data;
        
        // Poor filtering, or ...
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        // ... nice trilinear filtering.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
        glGenerateMipmap(GL_TEXTURE_2D);
        
        // Return the ID of the texture we just created
        return textureID;
    }
}