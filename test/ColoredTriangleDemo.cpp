//
//  ColorTriangleDemo.cpp
//  test
//
//  Created by Chukie on 15/9/1.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "ColoredTriangleDemo.h"

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
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,"/Users/chukie/Study/WorkWork/opengl_framework/test/resource/PointDemo.vert"));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,"/Users/chukie/Study/WorkWork/opengl_framework/test/resource/PointDemo.frag"));
        mShaderProgram->BuildProgram(shaders);
        
    }
    
    void ColoredTriangleDemo::Draw()
    {
        
    }
}