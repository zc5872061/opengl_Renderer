//
//  Common.h
//  test
//
//  Created by Chukie on 15/8/27.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#ifndef test_Common_h
#define test_Common_h
#include <GL/glew.h>
#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <map>
#include <assert.h>
#include <vector>
#include "Util.h"

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 480;

#define DeleteObject(object) if((object) != NULL) { delete object; object = NULL; }

#endif
