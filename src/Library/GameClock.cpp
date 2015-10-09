//
//  GameClock.cpp
//  test
//
//  Created by Chukie on 15/9/10.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "GameClock.h"
#include <GLFW/glfw3.h>


namespace Library
{
    GameClock::GameClock()
    {
        mStartTime = 0.0;
        mCurrentTime = 0.0;
        mLastTime = 0.0;
    }
    
    void GameClock::UpdateGameTime(GameTime& gameTime)
    {
        double time = glfwGetTime();
        mLastTime = mCurrentTime;
        mCurrentTime = time;
        gameTime.SetElapsedGameTime(mCurrentTime - mLastTime);
        gameTime.SetTotalGameTime(mCurrentTime);
        
    }
   
}
