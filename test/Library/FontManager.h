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
        void RenderText();
        
        
    protected:
        FontManager();
        ~FontManager();
        void init();
        static FontManager* mInstance;
        
    protected:
        std::map<GLchar,FONT::Charactar> Characters;
        GLuint mVAO;
        GLuint mVBO;
        ShaderProgram mShaderProgram;
    };
}
