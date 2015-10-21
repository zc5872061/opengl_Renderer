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
#include "testDemo.h"
#include "LightingDemo.h"
#include "CubeTextureDemo.h"
#include "FrameBufferDemo.h"


using namespace glm;

namespace Rendering
{
    RenderingGame::RenderingGame(const char* title,float width,float height):
    Game(title,width,height),
    m_Camera(nullptr),
    mPointDemo(nullptr),
    mColoredTriangleDemo(nullptr),
    mCubeDemo(nullptr),
    mGrid(nullptr),
    mWrapDemo(nullptr),
    mModelDemo(nullptr),
    mSkyBox(nullptr),
    mAmbientLightingDemo(nullptr),
    mDiffuseLightingDemo(nullptr),
    mBlinnPhongDemo(nullptr),
    mProxyModel(nullptr),
    mBillboardDemo(nullptr),
    mPaticleSystem(nullptr)
    {
        
    }
    
    RenderingGame::~RenderingGame()
    {
        
    }

    void RenderingGame::Initialize()
    {
        m_Camera = new FirstPersonCamera(this);
        mComponents.push_back(m_Camera);
        mPointDemo = new PointDemo(this,m_Camera);
        //mComponents.push_back(mPointDemo);
        
        
        mColoredTriangleDemo = new ColoredTriangleDemo(this,m_Camera);
        //mComponents.push_back(mColoredTriangleDemo);
        mSkyBox = new SkyBox(this,m_Camera,imgxPos,imgxNeg,imgyPos,imgyNeg,imgzPos,imgzNeg,10.0);
        //mComponents.push_back(mSkyBox);
       
        mGrid = new Grid(this,m_Camera);
        //mComponents.push_back(mGrid);
        
        mCubeDemo = new CubeDemo(this,m_Camera);
        //mComponents.push_back(mCubeDemo);
        
        mWrapDemo = new WrappingModesDemo(this,m_Camera);
        //mComponents.push_back(mWrapDemo);
        
        //mComponents.push_back(mColoredTriangleDemo);
//        
        mModelDemo = new ModelDemo(this,m_Camera);
        //mComponents.push_back(mModelDemo);
        mAmbientLightingDemo = new AmbientLightingDemo(this,m_Camera);
        //mComponents.push_back(mAmbientLightingDemo);
        
        mDiffuseLightingDemo = new DiffuseLightingDemo(this,m_Camera);
        //mComponents.push_back(mDiffuseLightingDemo);
        
        mBlinnPhongDemo = new BlinnPhongDemo(this,m_Camera);
        //mComponents.push_back(mBlinnPhongDemo);
        
        
        mProxyModel = new ProxyModel(this,m_Camera);
        //mComponents.push_back(mProxyModel);
        
        mBillboardDemo = new BillboardDemo(this,m_Camera);
        //mComponents.push_back(mBillboardDemo);
        
        mPaticleSystem = new PaticleSystem(this,m_Camera);
        //mComponents.push_back(mPaticleSystem);
        

        
        Rendering::testDemo* test = new Rendering::testDemo(this,m_Camera);
         //mComponents.push_back(test);
        
        Rendering::LightingDemo* light = new Rendering::LightingDemo(this,m_Camera);
        //mComponents.push_back(light);
        
        //Rendering::CubeTextureDemo* cubeTex = new Rendering::CubeTextureDemo(this,m_Camera);
        //mComponents.push_back(cubeTex);
        
        Rendering::FrameBufferDemo* mFrameBufferDemo = new Rendering::FrameBufferDemo(this,m_Camera);
        mComponents.push_back(mFrameBufferDemo);
        
        Game::Initialize();
        m_Camera->SetPosition(0, 5, 10);
        m_Camera->ApplyRotation(rotate(mat4(), 30.0f, Vector3Helper::Left));
        
        
        
    }
    
    void RenderingGame::Draw(GameTime gametime)
    {
        glEnable(GL_DEPTH_TEST);

        static const GLfloat one = 1.0f;
         glClearColor(49.0/255.0f, 77.0/255.0f, 121.0/255.0f, 1.0f);
        //glClearBufferfv(GL_COLOR, 0, &ColorHelper::CornflowerBlue[0]);
        //glClearBufferfv(GL_DEPTH, 0, &one);

        FontManager::GetInstance()->setProjViewMatrix(m_Camera->ViewProjectionMatrixOrth());
        Game::Draw(gametime);
        FontManager::GetInstance()->renderText("This is framebuffer sample", 0.0f, 40.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
//        
        glfwSwapBuffers(m_Window);
    }
    
    void RenderingGame::Shutdown()
    {
        Game::Shutdown();
    }
}