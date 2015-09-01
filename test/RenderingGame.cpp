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

namespace Rendering
{
    RenderingGame::RenderingGame(const char* title,float width,float height):
    Game(title,width,height),
    m_Camera(nullptr),
    mPointDemo(nullptr),
    mColoredTriangleDemo(nullptr)
    {
        
    }
    
    void RenderingGame::Initialize()
    {
        mPointDemo = new PointDemo(this,m_Camera);
        mColoredTriangleDemo = new ColoredTriangleDemo(this,m_Camera);
        mComponents.push_back(mPointDemo);
        mComponents.push_back(mColoredTriangleDemo);
        Game::Initialize();
    }
    
    void RenderingGame::Draw()
    {
        glClearBufferfv(GL_COLOR, 0, &ColorHelper::CornflowerBlue[0]);
        
        Game::Draw();
        
        glfwSwapBuffers(m_Window);
    }
    
    void RenderingGame::Shutdown()
    {
        Game::Shutdown();
    }
}