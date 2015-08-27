//
//  Game.cpp
//  test
//
//  Created by Chukie on 15/8/26.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Game.h"
#include <iostream>


namespace OglLibrary {
    
    Game* Game::m_Instance = nullptr;
    
    Game::Game()
    {
    }
    Game::~Game()
    {
    }
    
    bool Game::Run()
    {
        m_Instance = this;
        
        if(!InitializeWindow())
        {
            return false;
        }
        InitializeOpenGL();

        while (!glfwWindowShouldClose(m_Window)) {
            float ratio;
            int width, height;
            glfwGetFramebufferSize(m_Window, &width, &height);
            ratio = width / (float) height;
            glViewport(0, 0, width, height);

            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_DEPTH_BUFFER_BIT);
            glClearColor(255, 255, 255, 255);
            
           // glViewport(0, 0, width, height);
//            glClear(GL_COLOR_BUFFER_BIT);
//            glMatrixMode(GL_PROJECTION);
//            glLoadIdentity();
//            glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//            glMatrixMode(GL_MODELVIEW);
//            glLoadIdentity();
            //glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
            glBegin(GL_TRIANGLES);
            glColor3f(1.f, 0.f, 0.f);
            glVertex3f(-0.6f, -0.4f, 0.f);
            glColor3f(0.f, 1.f, 0.f);
            glVertex3f(0.6f, -0.4f, 0.f);
            glColor3f(0.f, 0.f, 1.f);
            glVertex3f(0.f, 0.6f, 0.f);
            glEnd();
            
            
            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
        return true;
    }
    
    void Game::Exit()
    {
        glfwSetWindowShouldClose(m_Window, GL_TRUE);
    }
    
    void Game::Initialize()
    {
       
            
    }
    
    bool Game::InitializeWindow()
    {
       

        if(!glfwInit())
        {
            std::cout<<"failed to initialize window"<<std::endl;
            return false;
        }
        
        
        m_Window = glfwCreateWindow(680, 480, "Hello world", nullptr, nullptr);
        if(!m_Window)
        {
            Shutdown();
            return false;
        }

        
        return true;
    }
    
    void Game::InitializeOpenGL()
    {
//        if (glewInit() != GLEW_OK)
//        {
//            std::cout<<"fail to initialize opengl"<<std::endl;
//        }
//        std::cout<<"Opengl Version"<<glGetString(GL_VERSION)<<std::endl;
//        std::cout<<"Opengl Version"<<glGetString(GL_EXTENSIONS)<<std::endl;
//        std::cout<<"Opengl Version"<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
    }
    
    void Game::Shutdown()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
}
