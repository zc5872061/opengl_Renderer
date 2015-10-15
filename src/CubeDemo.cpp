//
//  CubeDemo.cpp
//  test
//
//  Created by Chukie on 15/9/8.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "CubeDemo.h"
#include "Game.h"
#include "ColorHelper.h"
#include "Camera.h"
#include "Utility.h"
#include "ShaderProgram.h"
#include "VertexDeclarations.h"
#include "VectorHelper.h"
#include <glm/gtc/matrix_transform.hpp>


using namespace glm;

namespace Rendering
{
    const GLfloat CubeDemo::RotationRate = 180.0f;
    
    CubeDemo::CubeDemo(Game* game, Camera* camera)
    : DrawableGameComponent(game, camera), mVertexArrayObject(0), mVertexBuffer(0),
    mIndexBuffer(0), mWorldViewProjectionLocation(-1), mWorldMatrix()
    {
        mShaderProgram = new ShaderProgram();
    }
    
    CubeDemo::~CubeDemo()
    {
        glDeleteBuffers(1, &mIndexBuffer);
        glDeleteBuffers(1, &mVertexBuffer);
        glDeleteVertexArrays(1, &mVertexArrayObject);
    }
    
    void CubeDemo::Initialize()
    {
       
        
        // Build the shader program
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER, cubeVertexShaderStr));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,cubeFragShaderStr));
        mShaderProgram->BuildProgram(shaders);
        
        // Create the vertex buffer object
        VertexPositionColor vertices[] =
        {
            VertexPositionColor(vec4(-.5f, +.5f, -.5f, 1.0f), ColorHelper::Green),
            VertexPositionColor(vec4(+.5f, +.5f, -.5f, 1.0f), ColorHelper::Yellow),
            VertexPositionColor(vec4(+.5f, +.5f, +.5f, 1.0f), ColorHelper::White),
            VertexPositionColor(vec4(-.5f, +.5f, +.5f, 1.0f), ColorHelper::BlueGreen),
            
            VertexPositionColor(vec4(-.5f, -.5f, +.5f, 1.0f), ColorHelper::Blue),
            VertexPositionColor(vec4(+.5f, -.5f, +.5f, 1.0f), ColorHelper::Purple),
            VertexPositionColor(vec4(+.5f, -.5f, -.5f, 1.0f), ColorHelper::Red),
            VertexPositionColor(vec4(-.5f, -.5f, -.5f, 1.0f), ColorHelper::Black)
        };
        
        glGenBuffers(1, &mVertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        GLuint indices[] =
        {
            0, 2, 1,
            0, 3, 2,
            
            4, 6, 5,
            4, 7, 6,
            
            3, 5, 2,
            3, 4, 5,
            
            2, 6, 1,
            2, 5, 6,
            
            1, 6, 7,
            1, 7, 0,
            
            0, 4, 3,
            0, 7, 4
        };
        
        glGenBuffers(1, &mIndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        // Create the vertex array object
        glGenVertexArrays(1, &mVertexArrayObject);
        glBindVertexArray(mVertexArrayObject);
        
        glVertexAttribPointer(VertexAttributePosition, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), (void*)offsetof(VertexPositionColor, Position));
        glEnableVertexAttribArray(VertexAttributePosition);
        
        glVertexAttribPointer(VertexAttributeColor, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), (void*)offsetof(VertexPositionColor, Color));
        glEnableVertexAttribArray(VertexAttributeColor);
        
        glBindVertexArray(0);
        
        mWorldViewProjectionLocation = glGetUniformLocation(mShaderProgram->Program(), "WorldViewProjection");
        if (mWorldViewProjectionLocation == -1)
        {
            std::cout<<"glGetUniformLocation() did not find uniform location."<<std::endl;
        }
    }
    
    void CubeDemo::Draw(GameTime gametime)
    {
       
        glEnable(GL_DEPTH);
        glBindVertexArray(mVertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
        
        glUseProgram(mShaderProgram->Program());
        //std::cout<<"times:"<<glfwGetTime()<<std::endl;
//        for(int i = 0 ; i < 4; i ++)
//        {
//            for(int j = 0 ; j < 4; j ++)
//            {
//                std::cout<<mWorldMatrix[i][j]<< "             ";
//            }
//            std::cout<<std::endl;
//        }
        // Positions all containers
        glm::vec3 cubePositions[] = {
            glm::vec3( 1.0f,  0.0f,  0.0f),
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
        
        for (GLuint i = 0; i < 10; i++)
        {
            mat4 gMatrix = glm::translate(mWorldMatrix, cubePositions[i]);
            mat4 wvp = mCamera->ViewProjectionMatrix() * gMatrix;

            glUniformMatrix4fv(mWorldViewProjectionLocation, 1, GL_FALSE, &wvp[0][0]);
           
            
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            
        }
       
        glBindVertexArray(0);
        glEnable(GL_DEPTH);
    }
}
