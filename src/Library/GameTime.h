//
//  GameTime.h
//  test
//
//  Created by Chukie on 15/8/28.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#ifndef __test__GameTime__
#define __test__GameTime__
#include <sys/time.h>

namespace Library {
    class GameTime
    {
    public:
        GameTime();
        GameTime(double totalGameTime, double elapsedGameTime);
        
        double TotalGameTime() const;
        void SetTotalGameTime(double totalGameTime);
        
        double ElapsedGameTime() const;
        void SetElapsedGameTime(double elapsedGameTime);

        
    private:
        double mTotalGameTime;
        double mElapsedGameTime;
    };
}

#endif /* defined(__test__GameTime__) */
