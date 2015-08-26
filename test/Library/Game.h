//
//  Game.h
//  test
//
//  Created by Chukie on 15/8/26.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#ifndef __test__Game__
#define __test__Game__

namespace OglLibrary{
    class Game
    {
    public:
        Game();
        ~Game();
        virtual void Run();
        virtual void Exit();
        virtual void Initialize();
        
    protected:
        virtual void InitializeWindow();
        virtual void InitializeOpenGL();
        virtual void Shutdown();
        GLFWwindow* mWindow;
    };
}

#endif /* defined(__test__Game__) */
