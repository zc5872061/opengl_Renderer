//
//  Util.h
//  test
//
//  Created by Chukie on 15/9/15.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#pragma once

#include <string>

using namespace std;

//#define HOME

#ifdef HOME
#define cubeVertexShaderStr  "/Users/chukie/Study/WorkWork/opengl_framework/test/resource/CubeDemo.vert"
#define cubeFragShaderStr  "/Users/chukie/Study/WorkWork/opengl_framework/test/resource/CubeDemo.frag"
#define bassicVertexShaderStr  "/Users/chukie/Study/WorkWork/opengl_framework/test/resource/BasicEffect.vert"
#define bassicFragShaderStr  "/Users/chukie/Study/WorkWork/opengl_framework/test/resource/BasicEffect.frag"
#define WrappingVStr "/Users/chukie/Study/WorkWork/opengl_framework/test/resource/WrappingModesDemo.vert"
#define WrappingFStr "/Users/chukie/Study/WorkWork/opengl_framework/test/resource/WrappingModesDemo.frag"
#define ModelDemoVStr "/Users/chukie/Study/WorkWork/opengl_framework/test/resource/ModelDemo.vert"
#define ModelDemoFStr "/Users/chukie/Study/WorkWork/opengl_framework/test/resource/ModelDemo.frag"
#define imgStr "/Users/chukie/Study/WorkWork/opengl_framework/test/resource/Cover.tga"
#define img1Str "/Users/chukie/Study/WorkWork/opengl_framework/test/resource/Cover.jpg"
#else
#define cubeVertexShaderStr  "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/CubeDemo.vert"
#define cubeFragShaderStr  "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/CubeDemo.frag"
#define bassicVertexShaderStr  "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/BasicEffect.vert"
#define bassicFragShaderStr  "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/BasicEffect.frag"
#define WrappingVStr  "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/WrappingModesDemo.vert"
#define WrappingFStr "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/WrappingModesDemo.frag"
#define ModelDemoVStr  "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/ModelDemo.vert"
#define ModelDemoFStr "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/ModelDemo.frag"
#define SkyBoxVStr  "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/Skybox.vert"
#define SkyBoxFStr "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/Skybox.frag"
#define imgStr "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/Cover.jpg"
#define earthImgStr "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/EarthComposite.jpg"
#define sphereModel "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/Sphere.obj"

#define imgxPos "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/posx.jpg"
#define imgxNeg "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/negx.jpg"
#define imgyPos "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/posy.jpg"
#define imgyNeg "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/negy.jpg"
#define imgzPos "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/posz.jpg"
#define imgzNeg "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/negz.jpg"

#define AmbientLightVStr  "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/AmbientLightingDemo.vert"
#define AmbientLightFStr "/Users/chukie/Desktop/Demo/opengl_framework/test/resource/AmbientLightingDemo.frag"

#endif

