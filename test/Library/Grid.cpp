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
    
    const GLuint Grid::DefaultSize = 10;
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
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,"/Users/chukie/Desktop/Demo/opengl_framework/test/resource/BasicEffect.vert"));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,"/Users/chukie/Desktop/Demo/opengl_framework/test/resource/BasicEffect.frag"));
        mShaderProgram.BuildProgram(shaders);
        
        InitializeGrid();
        // Create the vertex array object
        glGenVertexArrays(1, &mVertexArrayObject);
        mShaderProgram.Initialize(mVertexArrayObject);
        glBindVertexArray(0);
        
    }
    
    void Grid::InitializeGrid()
    {
        mVertexCount = (mSize + 1)*4;
        VertexPositionColor* vertices = new VertexPositionColor[mVertexCount];
        float adjustedScale = mScale * 0.1f;
        float maxPosition = mSize * adjustedScale / 2;
        
        for (unsigned int i = 0, j = 0; i < mSize + 1; i++, j = 4 * i)
        {
            float position = maxPosition - (i * adjustedScale);
            
            // Vertical line
            vertices[j] = VertexPositionColor(vec4(position, 0.0f, maxPosition, 1.0f), mColor);
            vertices[j + 1] = VertexPositionColor(vec4(position, 0.0f, -maxPosition, 1.0f), mColor);
            
            // Horizontal line
            vertices[j + 2] = VertexPositionColor(vec4(maxPosition, 0.0f, position, 1.0f), mColor);
            vertices[j + 3] = VertexPositionColor(vec4(-maxPosition, 0.0f, position, 1.0f), mColor);
        }
        
        glDeleteBuffers(1, &mVertexBuffer);
        
        mShaderProgram.CreateVertexBuffer(vertices, mVertexCount, mVertexBuffer);
    }
    
    void Grid::Draw(GameTime gameTime)
    {
        glBindVertexArray(mVertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        
        mShaderProgram.Use();
        
        mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
        *(mShaderProgram.WorldViewProjection()) << wvp;
        
        glDrawArrays(GL_LINES, 0, mVertexCount);
        glBindVertexArray(0);
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