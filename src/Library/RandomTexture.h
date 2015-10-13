//
//  RandomTexture.h
//  OglRenderer
//
//  Created by Chukie on 15/10/13.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once

#include <GL/glew.h>
#include "Common.h"

namespace Library {
    class RandomTexture
    {
    public:
        RandomTexture();
        
        ~RandomTexture();
        
        bool InitRandomTexture(unsigned int Size);
        
        void Bind(GLenum TextureUnit);
    private:
        GLuint m_textureObj;
    };
}
