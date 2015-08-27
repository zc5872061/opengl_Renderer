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
namespace OglLibrary{
    class Game
    {
    protected:
        float m_Width;
        float m_Height;
        GLint mMajorVersion;
        GLint mMinorVersion;
    public:
        Game();
        ~Game();
        virtual bool Run();
        virtual void Exit();
        virtual void Initialize();
        
    protected:
        virtual bool InitializeWindow();
        virtual void InitializeOpenGL();
        virtual void Shutdown();
        GLFWwindow* m_Window;
        static Game* m_Instance;
    };
}

#endif /* defined(__test__Game__) */
