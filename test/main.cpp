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
#include <soil/SOIL.h>

using namespace std;
using namespace Library;
using namespace Rendering;


int main(int argc, const char * argv[]) {
    Assimp::Importer importer;
    unsigned int flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType;
    const aiScene* scene = importer.ReadFile("", flags);
    
    SOIL_load_OGL_texture("Content\\Textures\\EarthComposite.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB );
    
    //int i = scene->mFlags;
    RenderingGame* game = new RenderingGame("oglFrameWork",SCREEN_WIDTH,SCREEN_HEIGHT);
    
//    Library::Game* game = new Library::Game("oglFrameWork",SCREEN_WIDTH,SCREEN_HEIGHT);
    if(!game->Run())
    {
        std::cout<<"game run failed"<<std::endl;
    }
    else
    {
        std::cout<<"game exit"<<std::endl;
    }
    
//    const glm::vec4 CornflowerBlue = glm::vec4(0.392f, 0.584f, 0.929f, 1.0f);
//    
//    if (!glfwInit())
//    {
//        return -1;
//    }
//    
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Essentials", nullptr, nullptr);
//    if (window == nullptr)
//    {
//        return -1;
//    }
//    
//    glfwMakeContextCurrent(window);
//    cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << endl;
//    cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << endl;
//    cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
//    cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
//    
//    glViewport(0, 0, 800, 600);
//    GLuint vao;
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//    
//    while (!glfwWindowShouldClose(window))
//    {
//        glClear(GL_COLOR_BUFFER_BIT);
//        glClearColor(0.2, 0.3, 0.8, 1.0);
//        
//        glDrawArrays(GL_ARRAY_BUFFER, 0, 0);
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    
//    glfwDestroyWindow(window);
//    glfwTerminate();
    return 0;
}
