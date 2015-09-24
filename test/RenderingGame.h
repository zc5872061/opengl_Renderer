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
#include "ColoredTriangleDemo.h"
#include "CubeDemo.h"
#include "Grid.h"
#include "WrappingModesDemo.h"
#include "ModelDemo.h"

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
        virtual void Draw(GameTime gametime) override;
        virtual void Shutdown() override;
    private:
        FirstPersonCamera* m_Camera;
        PointDemo* mPointDemo;
        ColoredTriangleDemo* mColoredTriangleDemo;
        CubeDemo* mCubeDemo;
        Grid* mGrid;
        WrappingModesDemo* mWrapDemo;
        ModelDemo* mModelDemo;
    };
}

#endif /* defined(__test__RenderingGame__) */
