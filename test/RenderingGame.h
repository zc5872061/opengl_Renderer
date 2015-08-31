//
//  RenderingGame.h
//  test
//
//  Created by Chukie on 15/8/31.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#ifndef __test__RenderingGame__
#define __test__RenderingGame__

#include "Game.h"
#include "PointDemo.h"

using namespace Library;

namespace Library {
    class FirstPersonCamera;
}

namespace Rendering
{
    class RenderingGame:public Game
    {
    public:
        RenderingGame(const char* title,float width,float height);
    protected:
        virtual void Initialize() override;
        virtual void Draw() override;
        virtual void Shutdown() override;
    private:
        FirstPersonCamera* m_Camera;
        PointDemo* mPointDemo;
    };
}

#endif /* defined(__test__RenderingGame__) */
