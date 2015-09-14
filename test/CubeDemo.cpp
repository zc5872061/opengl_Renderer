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
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER, "/Users/chukie/Study/WorkWork/opengl_framework/test/resource/CubeDemo.vert"));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,"/Users/chukie/Study/WorkWork/opengl_framework/test/resource/CubeDemo.frag"));
        mShaderProgram->BuildProgram(shaders);
        
        // Create the vertex buffer object
        VertexPositionColor vertices[] =
        {
            VertexPositionColor(vec4(-1.0f, +1.0f, -1.0f, 1.0f), ColorHelper::Green),
            VertexPositionColor(vec4(+1.0f, +1.0f, -1.0f, 1.0f), ColorHelper::Yellow),
            VertexPositionColor(vec4(+1.0f, +1.0f, +1.0f, 1.0f), ColorHelper::White),
            VertexPositionColor(vec4(-1.0f, +1.0f, +1.0f, 1.0f), ColorHelper::BlueGreen),
            
            VertexPositionColor(vec4(-1.0f, -1.0f, +1.0f, 1.0f), ColorHelper::Blue),
            VertexPositionColor(vec4(+1.0f, -1.0f, +1.0f, 1.0f), ColorHelper::Purple),
            VertexPositionColor(vec4(+1.0f, -1.0f, -1.0f, 1.0f), ColorHelper::Red),
            VertexPositionColor(vec4(-1.0f, -1.0f, -1.0f, 1.0f), ColorHelper::Black)
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
        
        mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
//        for(int i = 0 ; i < 4; i ++)
//        {
//            for(int j = 0 ; j < 4; j ++)
//            {
//                std::cout<<wvp[i][j]<< "             ";
//            }
//            std::cout<<std::endl;
//        }
        glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
        // Camera matrix
        glm::mat4 View       = glm::lookAt(
                                           glm::vec3(5,5,5), // Camera is at (4,3,-3), in World Space
                                           glm::vec3(0,0,0), // and looks at the origin
                                           glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                           );
        // Model matrix : an identity matrix (model will be at the origin)
        glm::mat4 Model      = glm::mat4(1.0f);
        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication
        glUniformMatrix4fv(mWorldViewProjectionLocation, 1, GL_FALSE, &wvp[0][0]);
        
        glEnable(GL_CULL_FACE);
        //glFrontFace(GL_CCW);
        
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}
