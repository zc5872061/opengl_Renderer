//
//  PointDemo.cpp
//  test
//
//  Created by Chukie on 15/8/31.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "PointDemo.h"
#include "Game.h"
#include "Utility.h"

namespace Rendering
{
    
    PointDemo::PointDemo(Game* game, Camera* camera)
    : DrawableGameComponent(game, camera), mShaderProgram(0), mVertexArrayObject(0)
    {
    }
    
    PointDemo::~PointDemo()
    {
        glDeleteProgram(mShaderProgram);
        glDeleteVertexArrays(1, &mVertexArrayObject);
    }
    
    void PointDemo::Initialize()
    {
        GLint shader_ok;
        // Load and compile vertex shader
        std::vector<char> vertexShaderSource;
        Utility::LoadBinaryFile("../Resource/shader/PointDemo.vert", vertexShaderSource);
        GLchar* sourcePointer = &vertexShaderSource[0];
        GLint length = (GLint)vertexShaderSource.size();
        
        
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &sourcePointer, &length);
        glCompileShader(vertexShader);
        
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shader_ok);
        if(!shader_ok)
        {
            assert(false);
        }
        
        // Load and compile fragment shader
        std::vector<char> fragmentShaderSource;
        Utility::LoadBinaryFile("../Resource/shader/PointDemo.frag", fragmentShaderSource);
        sourcePointer = &fragmentShaderSource[0];
        length = (GLint)fragmentShaderSource.size();
        
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &sourcePointer, &length);
        glCompileShader(fragmentShader);
        
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shader_ok);
        if(!shader_ok)
        {
            assert(false);
        }
        
        // Create and link the shader program
        mShaderProgram = glCreateProgram();
        glAttachShader(mShaderProgram, vertexShader);
        glAttachShader(mShaderProgram, fragmentShader);
        glLinkProgram(mShaderProgram);
        GLint linkSuccess;
        glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &linkSuccess);
        if(linkSuccess == GL_FALSE)
        {
            assert(false);
        }
        
        
        // Clean up temporary shader objects
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
        // Create vertex array object
        //glGenVertexArrays(1, &mVertexArrayObject);
    }
    
    void PointDemo::Draw(GameTime gametime)
    {
        //glBindVertexArray(mVertexArrayObject);
        glUseProgram(mShaderProgram);
        glPointSize(80.0f);
        glDrawArrays(GL_POINTS, 0, 1);
        //glBindVertexArray(0);
    }
}
