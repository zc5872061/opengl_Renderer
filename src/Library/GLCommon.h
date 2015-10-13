//
//  GLCommon.h
//  OglRenderer
//
//  Created by Chukie on 15/10/13.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once
#include <GL/glew.h>
#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


#define GLCheckError() (glGetError() == GL_NO_ERROR)
#define COLOR_TEXTURE_UNIT              GL_TEXTURE0
#define COLOR_TEXTURE_UNIT_INDEX        0
#define SHADOW_TEXTURE_UNIT             GL_TEXTURE1
#define SHADOW_TEXTURE_UNIT_INDEX       1
#define NORMAL_TEXTURE_UNIT             GL_TEXTURE2
#define NORMAL_TEXTURE_UNIT_INDEX       2
#define RANDOM_TEXTURE_UNIT             GL_TEXTURE3
#define RANDOM_TEXTURE_UNIT_INDEX       3
#define DISPLACEMENT_TEXTURE_UNIT       GL_TEXTURE4
#define DISPLACEMENT_TEXTURE_UNIT_INDEX 4
#define MOTION_TEXTURE_UNIT             GL_TEXTURE5
#define MOTION_TEXTURE_UNIT_INDEX       5