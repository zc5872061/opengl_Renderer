//
//  LightingDemo.cpp
//  OglRenderer
//
//  Created by Chukie on 15/10/15.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "LightingDemo.h"
#include "SOIL.h"
#include <glm/glm.hpp>
#include <glm/glm/gtx/transform.hpp>

using namespace Library;


namespace Rendering
{
    
    LightingDemo::LightingDemo(Game* game, Camera* camera)
    : DrawableGameComponent(game, camera), mShaderProgram1(nullptr),mVAO1(-1),mVBO1(-1)
    {
    }
    
    LightingDemo::~LightingDemo()
    {
        glDeleteProgram(mShaderProgram1->Program());
    }
    
    void LightingDemo::Initialize()
    {
        mShaderProgram1 = new ShaderProgram;
        vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,"../Resource/shader/LightingDemo/light_casters.vs"));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,"../Resource/shader/LightingDemo/light_casters.frag"));
        mShaderProgram1->BuildProgram(shaders);
        
        // Set up vertex data (and buffer(s)) and attribute pointers
        GLfloat vertices[] = {
            // Positions          // Normals           // Texture Coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
            
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
            
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
            
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };
        // Positions all containers
        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
        
        //gen vbo vao
        glGenVertexArrays(1,&mVAO1);
        glGenBuffers(1,&mVBO1);
        
        //bind vbo
        glBindBuffer(GL_ARRAY_BUFFER,mVBO1);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
        
        //bind vao
        glBindVertexArray(mVAO1);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GL_FLOAT),(GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        
        //gen light vao
        glGenVertexArrays(1,&mVAO2);
        //bind vao,vbo
        glBindVertexArray(mVAO2);
        glBindBuffer(GL_ARRAY_BUFFER,mVBO1);
        
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
        
        //gen texture
        glGenTextures(1, &mDiffuseMap);
        glGenTextures(1, &mSpecularMap);
        glGenTextures(1, &mEmissionMap);
        
        int height;
        int width;
        
        unsigned char* image;
        // Diffuse map
        image = SOIL_load_image("../Resource/pic/LightingDemo/container2.png", &width, &height, 0, SOIL_LOAD_RGB);
        glBindTexture(GL_TEXTURE_2D, mDiffuseMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        
        // Specular map
        image = SOIL_load_image("../Resource/pic/LightingDemo/container2_specular.png", &width, &height, 0, SOIL_LOAD_RGB);
        glBindTexture(GL_TEXTURE_2D, mSpecularMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        mShaderProgram1->Use();
        glUniform1i(glGetUniformLocation(mShaderProgram1->Program(), "material.diffuse"),  0);
        glUniform1i(glGetUniformLocation(mShaderProgram1->Program(), "material.specular"), 1);
        
    }
    
    void LightingDemo::Draw(GameTime gametime)
    {
        
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glFrontFace(GL_CCW);
        // Positions all containers
        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
//            glm::vec3( 2.0f,  5.0f, -15.0f),
//            glm::vec3(-1.5f, -2.2f, -2.5f),
//            glm::vec3(-3.8f, -2.0f, -12.3f),
//            glm::vec3( 2.4f, -0.4f, -3.5f),
//            glm::vec3(-1.7f,  3.0f, -7.5f),
//            glm::vec3( 1.3f, -2.0f, -2.5f),
//            glm::vec3( 1.5f,  2.0f, -2.5f),
//            glm::vec3( 1.5f,  0.2f, -1.5f),
//            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
        mShaderProgram1->Use();
        
        GLint lightPosLoc             = glGetUniformLocation(mShaderProgram1->Program(), "light.position");
        GLint lightSpotdirLoc         = glGetUniformLocation(mShaderProgram1->Program(), "light.direction");
        GLint lightSpotCutOffLoc      = glGetUniformLocation(mShaderProgram1->Program(), "light.cutOff");
        GLint lightSpotOuterCutOffLoc = glGetUniformLocation(mShaderProgram1->Program(), "light.outerCutOff");
        GLint viewPosLoc              = glGetUniformLocation(mShaderProgram1->Program(), "viewPos");
        
        glUniform3f(lightPosLoc,             mCamera->Position().x, mCamera->Position().y, mCamera->Position().z);
        glUniform3f(lightSpotdirLoc,         mCamera->Direction().x, mCamera->Direction().y, mCamera->Direction().z);
        glUniform1f(lightSpotCutOffLoc,      glm::cos(glm::radians(12.5f)));
        glUniform1f(lightSpotOuterCutOffLoc, glm::cos(glm::radians(17.5f)));
        glUniform3f(viewPosLoc,              mCamera->Position().x, mCamera->Position().y, mCamera->Position().z);
        
        // Set lights properties
        glUniform3f(glGetUniformLocation(mShaderProgram1->Program(), "light.ambient"),   0.1f, 0.1f, 0.1f);
        // We set the diffuse intensity a bit higher; note that the right lighting conditions differ with each lighting method and environment.
        // Each environment and lighting type requires some tweaking of these variables to get the best out of your environment.
        glUniform3f(glGetUniformLocation(mShaderProgram1->Program(), "light.diffuse"),   0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(mShaderProgram1->Program(), "light.specular"),  1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(mShaderProgram1->Program(), "light.constant"),  1.0f);
        glUniform1f(glGetUniformLocation(mShaderProgram1->Program(), "light.linear"),    0.09);
        glUniform1f(glGetUniformLocation(mShaderProgram1->Program(), "light.quadratic"), 0.032);
        // Set material properties
        glUniform1f(glGetUniformLocation(mShaderProgram1->Program(), "material.shininess"), 32.0f);
        
        
        // Create camera transformations
        glm::mat4 view;
        view = mCamera->ViewMatrix();
        
        glm::mat4 projection = mCamera->ProjectionMatrix();
    
        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(mShaderProgram1->Program(), "model");
        GLint viewLoc  = glGetUniformLocation(mShaderProgram1->Program(), "view");
        GLint projLoc  = glGetUniformLocation(mShaderProgram1->Program(), "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
        
        // Bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mDiffuseMap);
        // Bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mSpecularMap);
        
        glm::mat4 model;
        glBindVertexArray(mVAO1);
        for (GLuint i = 0; i < 1; i++)
        {
            model = glm::mat4();
            model = glm::translate(model, cubePositions[i]);
            GLfloat angle = 20.0f * i;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);
        glDisable(GL_DEPTH_TEST);
    }
}