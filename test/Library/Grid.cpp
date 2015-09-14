//
//  Grid.cpp
//  test
//
//  Created by Chukie on 15/9/12.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Grid.h"
#include "VectorHelper.h"

using namespace Library;

using namespace glm;

namespace Library {
    
    const GLuint Grid::DefaultSize = 160;
    const GLuint Grid::DefaultScale = 16;
    const glm::vec4 Grid::DefaultColor = glm::vec4(0.961f, 0.871f, 0.702f, 1.0f);
    
    Grid::Grid(Game* game,Camera* camera):
    DrawableGameComponent(game,camera)
    {
        mCamera = camera;
        mPosition = Vector3Helper::Zero;
        mSize = DefaultSize;
        mScale = DefaultScale;
        mColor = DefaultColor;
        mVertexCount = 0;
    }
    
    Grid::~Grid()
    {
        glDeleteBuffers(1, &mVertexBuffer);
        glDeleteVertexArrays(1, &mVertexArrayObject);
    }
    
    void Grid::Initialize()
    {
        
    }
    
    void Grid::Draw(GameTime gameTime)
    {
        
    }
    
    const glm::vec3& Grid::Position() const
    {
        return mPosition;
    }
    
    const glm::vec4& Grid::Color() const
    {
        return mColor;
    }
    
    const GLuint Grid::Size() const
    {
        return mSize;
    }
    
    const GLuint Grid::Scale() const
    {
        return mScale;
    }
    
    void Grid::SetPosition(const glm::vec3& position)
    {
        mPosition = position;
    }
    
    void Grid::SetPosition(float x, float y, float z)
    {
        mPosition.x = x;
        mPosition.y = y;
        mPosition.z = z;
    }
    
    void Grid::SetColor(const glm::vec4& color)
    {
        mColor = color;
    }
    
    void Grid::SetSize(GLuint size)
    {
        mSize = size;
    }
    
    void Grid::SetScale(GLuint scale)
    {
        mScale = scale;
    }
    
}