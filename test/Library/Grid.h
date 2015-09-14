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
        
        
        const glm::vec3& Position() const;
        const glm::vec4& Color() const;
        const GLuint Size() const;
        const GLuint Scale() const;
        
        void SetPosition(const glm::vec3& position);
        void SetPosition(float x, float y, float z);
        void SetColor(const glm::vec4& color);
        void SetSize(GLuint size);
        void SetScale(GLuint scale);
        
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
