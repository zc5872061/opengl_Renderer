//
//  Game.h
//  test
//
//  Created by Chukie on 15/8/26.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#ifndef __test__Game__
#define __test__Game__


#include "Common.h"
#include "GameComponent.h"
#include <string>
#include <vector>

namespace Library{
    class Game
    {
    protected:
        float m_Width;
        float m_Height;
        GLint mMajorVersion;
        GLint mMinorVersion;
        std::string m_Name;
        static double m_xClickPos;
        static double m_yClickPos;
        
    public:
        Game(const char* name,float width,float height);
        ~Game();
        
        GLFWwindow* Window() const {return m_Window;}
        int ScreenWidth() const;
        int ScreenHeight() const;
        float AspectRatio() const;

        
        virtual bool Run();
        virtual void Exit();
        virtual void Initialize();
        virtual void Update();
        virtual void Draw();
    protected:
        virtual bool InitializeWindow();
        virtual void InitializeOpenGL();
        virtual void Shutdown();
        static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void OnResizeWindow(GLFWwindow* window,int width,int height);
        static void OnMouseClick(GLFWwindow* window,int button,int action,int mods);
        static void OnMouseCursor(GLFWwindow* window,double xpos,double ypos);
        GLFWwindow* m_Window;
        static Game* m_Instance;
        std::vector<GameComponent*> mComponents;
    };
}

#endif /* defined(__test__Game__) */
