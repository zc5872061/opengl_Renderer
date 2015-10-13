//
//  testDemo.cpp
//  OglRenderer
//
//  Created by Chukie on 15/10/13.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "testDemo.h"
#include "Game.h"
#include "Utility.h"

namespace Rendering
{
    
    testDemo::testDemo(Game* game, Camera* camera)
    : DrawableGameComponent(game, camera), mShaderProgram(0)
    {
    }
    
    testDemo::~testDemo()
    {
        glDeleteProgram(mShaderProgram);
    }
    
    void testDemo::Initialize()
    {
        glm::vec3 Vertices[3];
        Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
        Vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
        Vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    }
    
    void testDemo::Draw(GameTime gametime)
    {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glDisableVertexAttribArray(0);
    }
}
