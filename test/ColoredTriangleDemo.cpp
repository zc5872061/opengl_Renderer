//
//  ColorTriangleDemo.cpp
//  test
//
//  Created by Chukie on 15/9/1.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "ColoredTriangleDemo.h"
#include "VertexDeclarations.h"
#include "ColorHelper.h"

using namespace glm;

namespace Rendering
{
    ColoredTriangleDemo::ColoredTriangleDemo(Game* game,Camera* camera)
    :DrawableGameComponent(game,camera)
    {
        mShaderProgram = new ShaderProgram();
        mVertexArrayObject = 0;
        mVertexBuffer = 0;
    }
    
    ColoredTriangleDemo::~ColoredTriangleDemo()
    {
        if(mShaderProgram)
        {
            delete mShaderProgram;
            mShaderProgram = nullptr;
        }
        glDeleteBuffers(1,&mVertexBuffer);
        glDeleteVertexArrays(1,&mVertexArrayObject);
    }
    
    void ColoredTriangleDemo::Initialize()
    {
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,"/Users/chukie/Desktop/Demo/opengl_framework/test/resource/ColoredTriangleDemo.vert"));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,"/Users/chukie/Desktop/Demo/opengl_framework/test/resource/resource/ColoredTriangleDemo.frag"));
        mShaderProgram->BuildProgram(shaders);
        // Create the vertex buffer
        VertexPositionColor vertices[] =
        {
            VertexPositionColor(vec4(0.75f, -0.25f, 0.0f, 1.0f), ColorHelper::Red),
            VertexPositionColor(vec4(0.0f, 0.5f, 0.0f, 1.0f), ColorHelper::Green),
            VertexPositionColor(vec4(-0.75f, -0.25f, 0.0f, 1.0f), ColorHelper::Blue)
        };
        
        glGenBuffers(1, &mVertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        // Create vertex array object
        glGenVertexArrays(1, &mVertexArrayObject);
        glBindVertexArray(mVertexArrayObject);
        
        glVertexAttribPointer(VertexAttributePosition, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), (void*)offsetof(VertexPositionColor, Position));
        glEnableVertexAttribArray(VertexAttributePosition);
        
        glVertexAttribPointer(VertexAttributeColor, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), (void*)offsetof(VertexPositionColor, Color));
        glEnableVertexAttribArray(VertexAttributeColor);
        
        glBindVertexArray(0);
    }
    
    void ColoredTriangleDemo::Draw(GameTime gametime)
    {
        glBindVertexArray(mVertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glUseProgram(mShaderProgram->Program());
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }
}