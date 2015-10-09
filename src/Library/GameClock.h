//
//  GameClock.h
//  test
//
//  Created by Chukie on 15/9/10.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once

#include "GameTime.h"
namespace Library
{
    class GameTime;
    
    class GameClock
    {
    public:
        GameClock();
        
//        const float StartTime() const;
//        const float CurrentTime() const;
//        const float LastTime() const;
//        
//        void Reset();
//        double GetFrequency() const;
//        void GetTime(float time) const;
        void UpdateGameTime(GameTime& gameTime);
        
    private:
        GameClock(const GameClock& rhs);
        GameClock& operator=(const GameClock& rhs);
        
        double mStartTime;
        double mCurrentTime;
        double mLastTime;
    };
}