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
        ~GameTime();
        
        void initialize();
        void shutDown();
        double getElapsedTime();
        
    private:
        double	m_startTimeInMicroSec;
        double	m_endTimeInMicroSec;
        bool	m_stopped;
        
        timeval m_startCount;
        timeval m_endCount;
    };
}

#endif /* defined(__test__GameTime__) */
