//
//  Game.cpp
//  test
//
//  Created by Chukie on 15/8/26.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Game.h"
#include "DrawableGameComponent.h"
#include <iostream>


namespace Library {
    
    Game* Game::m_Instance = nullptr;
    double Game::m_xClickPos = 0;
    double Game::m_yClickPos = 0;
    
    Game::Game(const char* name,float width,float height):
    m_Name(name),
    m_Width(width),
    m_Height(height)
    {
       
    }
    
    Game::~Game()
    {
        mComponents.clear();
    }
    
    bool Game::Run()
    {
        m_Instance = this;
        
        if(!InitializeWindow())
        {
            return false;
        }
        InitializeOpenGL();
        Initialize();
        
        while (!glfwWindowShouldClose(m_Window)) {
            //const glm::vec4 CornflowerBlue = glm::vec4(0.392f, 0.584f, 0.929f, 1.0f);
            //glClearBufferfv(GL_COLOR, 0, &CornflowerBlue[0]);
            //std::cout<<glfwGetTime()<<std::endl;
//            float ratio;
//            int width, height;
//            glfwGetFramebufferSize(m_Window, &width, &height);
//            ratio = width / (float) height;
//            glViewport(0, 0, width, height);
//
//            glClear(GL_COLOR_BUFFER_BIT);
//            glClear(GL_DEPTH_BUFFER_BIT);
            //glClearColor(255, 255, 255, 255);
            
           // glViewport(0, 0, width, height);
//            glClear(GL_COLOR_BUFFER_BIT);
//            glMatrixMode(GL_PROJECTION);
//            glLoadIdentity();
//            glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//            glMatrixMode(GL_MODELVIEW);
//            glLoadIdentity();
            //glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
//            glBegin(GL_TRIANGLES);
//            glColor3f(1.f, 0.f, 0.f);
//            glVertex3f(-0.6f, -0.4f, 0.f);
//            glColor3f(0.f, 1.f, 0.f);
//            glVertex3f(0.6f, -0.4f, 0.f);
//            glColor3f(0.f, 0.f, 1.f);
//            glVertex3f(0.f, 0.6f, 0.f);
//            glEnd();
            m_GameClock.UpdateGameTime(m_GameTime);
            std::cout<<m_GameTime.TotalGameTime()<<std::endl;
            std::cout<<m_GameTime.ElapsedGameTime()<<std::endl;
            Update();
            Draw();
//            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
        return true;
    }
    
    void Game::Exit()
    {
        glfwSetWindowShouldClose(m_Window, GL_TRUE);
    }
    
    int Game::ScreenWidth() const
    {
        return m_Width;
    }
    
    int Game::ScreenHeight() const
    {
        return m_Height;
    }
    
    float Game::AspectRatio() const
    {
        return static_cast<float>(m_Width) / m_Height;
    }
    
    void Game::Initialize()
    {
        for (GameComponent* component : mComponents)
        {
            component->Initialize();
        }
    }
    void Game::Update()
    {
        for (GameComponent* component : mComponents)
        {
            if (component->Enabled())
            {
                component->Update();
            }
        }
    }
    void Game::Draw()
    {
        for (GameComponent* component : mComponents)
        {
            if(component->GetDrawAble() == true)
            {
                DrawableGameComponent* drawableGameComponent = dynamic_cast<DrawableGameComponent*>(component);
                drawableGameComponent->Draw();
            }
        }
    }

    bool Game::InitializeWindow()
    {
        if(!glfwInit())
        {
            std::cout<<"failed to initialize window"<<std::endl;
            return false;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), nullptr, nullptr);
        if(!m_Window)
        {
            Shutdown();
            return false;
        }
        glfwMakeContextCurrent(m_Window);
        glfwSetKeyCallback(m_Window, Game::OnKey);
        glfwSetWindowSizeCallback(m_Window, Game::OnResizeWindow);
        glfwSetMouseButtonCallback(m_Window,Game::OnMouseClick);
        glfwSetCursorPosCallback(m_Window,Game::OnMouseCursor);
        std::cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) <<std::endl;
        std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) <<std::endl;
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) <<std::endl;
        std::cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) <<std::endl;
        return true;
    }
    
    void Game::InitializeOpenGL()
    {
        glewExperimental = GL_TRUE;
        if(glewInit() != GLEW_OK)
        {
            std::cout<<"glew init failed"<<std::endl;
        }
        glGetIntegerv(GL_MAJOR_VERSION, &mMajorVersion);
        glGetIntegerv(GL_MINOR_VERSION, &mMinorVersion);
        
        
        //GLuint test;
        //glGenVertexArrays(1, &test);
    }
    
    void Game::Shutdown()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
    
    void Game::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
    
    void Game::OnResizeWindow(GLFWwindow* window,int width,int height)
    {
        glViewport(0, 0, width, height);
    }

    void Game::OnMouseCursor(GLFWwindow* window,double xpos,double ypos)
    {
        m_xClickPos = xpos;
        m_yClickPos = ypos;
    }
    
    void Game::OnMouseClick(GLFWwindow* window,int button,int action,int mods)
    {
        if(button == GLFW_MOUSE_BUTTON_LEFT)
        {
            std::cout<<"xpos:"<<m_xClickPos<<"ypos:"<<m_yClickPos<<std::endl;
        }
    }
}
