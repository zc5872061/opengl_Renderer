//
//  Common.cpp
//  OglRenderer
//
//  Created by Chukie on 15/10/13.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Common.h"

namespace Common {
    float RandomFloat()
    {
        float Max = RAND_MAX;
        return ((float)RANDOM() / Max);
    }
}