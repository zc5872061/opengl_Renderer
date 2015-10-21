//
//  CubeTextureDemo.cpp
//  OglRenderer
//
//  Created by Chukie on 15/10/18.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "CubeTextureDemo.h"
#include "VertexDeclarations.h"
#include "SOIL.h"
#include <glm/glm/gtx/transform.hpp>
#include "Camera.h"

using namespace glm;


namespace Rendering {
    CubeTextureDemo::CubeTextureDemo(Game* game, Camera* camera):
    DrawableGameComponent(game,camera)
    {
        mShaderProgram = new ShaderProgram;
    }
    
    CubeTextureDemo::~CubeTextureDemo()
    {
        
    }
    
    void CubeTextureDemo::Initialize()
    {
        // Build the shader program
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER, "../Resource/shader/CubeDemoTex.vert"));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,"../Resource/shader/CubeDemoTex.frag"));
        mShaderProgram->BuildProgram(shaders);
        
        glGenVertexArrays(1, &mVAO);
        glBindVertexArray(mVAO);
        glGenBuffers(1, &mVBO);
        
        GLfloat vertices[] = {
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

            -1.0f, -1.5f, -1.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
             1.0f, -1.5f, -1.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
             1.0f,  -1.5f, 1.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
             1.0f,  -1.5f, 1.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -1.0f,  -1.5f, 1.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.5f, -1.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
        };
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        // Specify the layout of the vertex data
        //GLint posAttrib = glGetAttribLocation(mShaderProgram->Program(), "position");
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(0);
        
        //GLint colAttrib = glGetAttribLocation(mShaderProgram->Program(), "color");
        
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        
        mColorTexture = SOIL_load_OGL_texture("../Resource/pic/test.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB );
        
        mWorldViewProjectionLocation = glGetUniformLocation(mShaderProgram->Program(), "WorldViewProjection");
    }
    
    void CubeTextureDemo::Draw(GameTime gametime)
    {
        GLint uniColor = glGetUniformLocation(mShaderProgram->Program(), "overrideColor");
        glEnable(GL_DEPTH);
        mShaderProgram->Use();
        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBindTexture(GL_TEXTURE_2D, mColorTexture);
        
        mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
        mat4 viewMatrix = mCamera->ViewMatrix() * mWorldMatrix;
 
        wvp = mCamera->ProjectionMatrix()*viewMatrix;
        glUniformMatrix4fv(mWorldViewProjectionLocation, 1, GL_FALSE, &wvp[0][0]);
        

        
        
       // model = glm::scale(glm::translate(mWorldMatrix, glm::vec3(0, 0, -1)), glm::vec3(1, 1, -1));
        glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        

        glEnable(GL_STENCIL_TEST);
        
        // Draw floor
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilMask(0xFF);
        glDepthMask(GL_FALSE);
        glClear(GL_STENCIL_BUFFER_BIT);
        
        glBindTexture(GL_TEXTURE_2D, 0);
        glDrawArrays(GL_TRIANGLES, 36, 6);
        
        // Draw cube reflection
        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDepthMask(GL_TRUE);
        
        mat4 model = glm::scale(glm::translate(mWorldMatrix, glm::vec3(0, -1.5, 0)), glm::vec3(1, -1, 1));
        wvp = mCamera->ViewProjectionMatrix() * model;

        

        glUniformMatrix4fv(mWorldViewProjectionLocation, 1, GL_FALSE, &wvp[0][0]);
        glBindTexture(GL_TEXTURE_2D, mColorTexture);
        glUniform3f(uniColor, 0.3f, 0.3f, 0.3f);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDisable(GL_STENCIL_TEST);
        glBindVertexArray(0);
    }
}