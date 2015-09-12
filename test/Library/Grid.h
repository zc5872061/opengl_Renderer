//
//  Grid.h
//  test
//
//  Created by Chukie on 15/9/12.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once

#include "Common.h"
#include "DrawableGameComponent.h"

namespace Library {
    class Grid:public DrawableGameComponent
    {
    public:
        Grid(Game* game,Camera* camera);
        ~Grid();
        
        virtual void Initialize() override;
        virtual void Draw(GameTime gameTime) override;
    private:
        static const GLuint DefaultSize;
        static const GLuint DefaultScale;
        static const glm::vec4 DefaultColor;
        
        GLuint mVertexArrayObject;
        GLuint mVertexBuffer;
        
        glm::vec3 mPosition;
        GLuint mSize;
        GLuint mScale;
        glm::vec4 mColor;
        glm::mat4 mWorldMatrix;
        unsigned int mVertexCount;
    };
}
