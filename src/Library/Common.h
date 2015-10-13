//
//  Common.h
//  test
//
//  Created by Chukie on 15/8/27.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#pragma once

#include <iostream>
#include <string>
#include <map>
#include <assert.h>
#include <vector>
#include <stdlib.h>
#include "Util.h"
#include "GLCommon.h"
const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 480;

typedef  unsigned int UINT;
#define DeleteObject(object) if((object) != NULL) { delete object; object = NULL; }
#define FOR(q,n) for(int q=0;q<n;q++)
#define RANDOM random
#define ZERO_MEM(a) memset(a, 0, sizeof(a))


namespace Common {
    float RandomFloat();
}




