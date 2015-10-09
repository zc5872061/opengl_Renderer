//
//  FontManager.cpp
//  OglFramework
//
//  Created by Chukie on 15/10/9.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "FontManager.h"

namespace Library {
    FontManager* FontManager::mInstance = nullptr;
    
    FontManager* FontManager::GetInstance()
    {
        if(mInstance == nullptr)
        {
            mInstance = new FontManager;
        }
        return mInstance;
    }
   
    FontManager::FontManager():
    mVAO(-1),
    mVBO(-1)
    {
        init();
    }
    
    FontManager::~FontManager()
    {
        
    }
    
    void FontManager::init()
    {
        //shader
        //build shader program
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,ModelDemoVStr));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,ModelDemoFStr));
        mShaderProgram.BuildProgram(shaders);
        
        //free type
        FT_Library ft;
        if(FT_Init_FreeType(&ft))
        {
            std::cout<<"error init freetype"<<std::endl;
        }
        
        FT_Face face;
        if(FT_New_Face(ft, "", 0, &face))
        {
            std::cout<<"error init face"<<std::endl;
        }
        
        FT_Set_Pixel_Sizes(face, 0, 48);
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        for(GLubyte c = 0; c < 128; c++)
        {
            if(FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout<<"failed to load "<<std::endl;
                continue;
            }
            
            GLuint texture;
            
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            FONT::Charactar character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width,face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left,face->glyph->bitmap_top),
                static_cast<GLuint>(face->glyph->advance.x)
            };
            
            Characters.insert(std::pair<GLchar,FONT::Charactar>(c,character));
        }
        
        glBindTexture(GL_TEXTURE_2D, 0);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        
        glGenVertexArrays(1,&mVAO);
        glBindVertexArray(mVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4*sizeof(GLfloat),0);
        glBindVertexArray(0);
        
        glGenBuffers(1,&mVBO);
        glBindBuffer(GL_ARRAY_BUFFER,mVBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*6*4,NULL,GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }
}


