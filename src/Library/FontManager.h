//
//  FontManager.h
//  OglFramework
//
//  Created by Chukie on 15/10/9.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#pragma once
#include "Common.h"
#include "ShaderProgram.h"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Library {
    
    namespace FONT
    {
        struct Charactar
        {
            GLuint TextureID;
            glm::ivec2 Size;
            glm::ivec2 Bearing;
            GLuint Advance;
        };
    };
    
    class FontManager
    {
    public:
        static FontManager* GetInstance();
        void renderText(std::string text,GLfloat x,GLfloat y,GLfloat scale,glm::vec3 color);
        void setProjViewMatrix(glm::mat4 projViewMat) { mProjViewMat = projViewMat;}
        
    protected:
        FontManager();
        ~FontManager();
        void init();
        static FontManager* mInstance;
       
    protected:
        std::map<GLchar,FONT::Charactar> Characters;
        GLuint mVAO;
        GLuint mVBO;
        GLint mWorldViewProjectionLocation;
        ShaderProgram mShaderProgram;
        glm::mat4 mProjViewMat;
    };
}
