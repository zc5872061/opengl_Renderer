//
//  RenderingGame.cpp
//  test
//
//  Created by Chukie on 15/8/31.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "RenderingGame.h"
#include "FirstPersonCamera.h"
#include "ColorHelper.h"
#include <glm/gtc/matrix_transform.hpp>
#include "VectorHelper.h"

using namespace glm;

namespace Rendering
{
    RenderingGame::RenderingGame(const char* title,float width,float height):
    Game(title,width,height),
    m_Camera(nullptr),
    mPointDemo(nullptr),
    mColoredTriangleDemo(nullptr),
    mCubeDemo(nullptr)
    {
        
    }
    
    void RenderingGame::Initialize()
    {
        m_Camera = new FirstPersonCamera(this);
        mComponents.push_back(m_Camera);
        mPointDemo = new PointDemo(this,m_Camera);
        mColoredTriangleDemo = new ColoredTriangleDemo(this,m_Camera);
        mCubeDemo = new CubeDemo(this,m_Camera);
        mComponents.push_back(mCubeDemo);
        //mComponents.push_back(mColoredTriangleDemo);
        Game::Initialize();
        m_Camera->SetPosition(0, 5, 10);
        m_Camera->ApplyRotation(rotate(mat4(), 30.0f, Vector3Helper::Left));
    }
    
    void RenderingGame::Draw()
    {
        static const GLfloat one = 1.0f;
        glClearBufferfv(GL_COLOR, 0, &ColorHelper::CornflowerBlue[0]);
        glClearBufferfv(GL_DEPTH, 0, &one);
        Game::Draw();
        
        glfwSwapBuffers(m_Window);
    }
    
    void RenderingGame::Shutdown()
    {
        Game::Shutdown();
    }
}