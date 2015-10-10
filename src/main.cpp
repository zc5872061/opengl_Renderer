//
//  main.cpp
//  test
//
//  Created by Chukie on 15/8/7.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#define GLFW_INCLUDE_GLCOREARB
#include <iostream>
#include <ctime>
#include <map>
//#include "Game.h"
#include "RenderingGame.h"
#include <assimp/include/scene.h>
#include <assimp/include/Importer.hpp>
#include <assimp/include/postprocess.h>
#include <CoreFoundation/CoreFoundation.h>
#include <soil/SOIL.h>
#include "VertexDeclarations.h"
#include "Model.h"
#include <stdio.h>
#include <ft2build.h>
#include FT_FREETYPE_H


using namespace std;
using namespace Library;
using namespace Rendering;


int main(int argc, const char * argv[]) {
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if(!CFURLGetFileSystemRepresentation(resourceURL,TRUE, (UInt8*)path, PATH_MAX))
    {
        
    }
#endif
    //FILE * file = fopen("../Resource/Cover.jpg","rb");
    RenderingGame* game = new RenderingGame("oglRenderer",SCREEN_WIDTH,SCREEN_HEIGHT);
    
    if(!game->Run())
    {
        std::cout<<"game run failed"<<std::endl;
    }
    else
    {
        std::cout<<"game exit"<<std::endl;
    }
    
    //Model* model = new Model("/Users/chukie/Study/WorkWork/opengl_framework/test/resource/dragon.obj",true);
//    Model* model = new Model("/Users/chukie/Desktop/dragon.obj",true);
//    return 0;
}
