//
//  ProxyModel.cpp
//  OglFramework
//
//  Created by Chukie on 15/10/7.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//



#include "ProxyModel.h"
#include "Game.h"
#include "ShaderProgram.h"
#include "Camera.h"

using namespace glm;
using namespace Library;

namespace Library {
    ProxyModel::ProxyModel(Game* game, Camera* camera)
    :DrawableGameComponent(game,camera),
    mModel(nullptr),
    mModelFileName(),
    mShaderProgram(),
    mVertexArrayObject(-1),
    mVertexBuffer(-1),
    mIndexBuffer(-1),
    mIndexCount(0),
    mWorldMatrix(),
    mScaleMatrix()
    {
        
    }
    
    ProxyModel::~ProxyModel()
    {
        DeleteObject(mModel);
        glDeleteBuffers(1,&mVertexBuffer);
        glDeleteBuffers(1,&mIndexBuffer);
        glDeleteVertexArrays(1,&mVertexArrayObject);
    }
    
    void ProxyModel::Initialize()
    {
        //compile shaders program
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,bassicVertexShaderStr));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,bassicFragShaderStr));
        
        mShaderProgram.BuildProgram(shaders);
        
        mModel = new Model(dragonModel,true);
        
        // Create the vertex and index buffers
        Mesh* mesh = mModel->Meshes().at(0);
        mShaderProgram.createVertexBuffer(*mesh, mVertexBuffer);
        mesh->CreateIndexBuffer(mIndexBuffer);
        mIndexCount = mesh->Indices().size();
        
        // Create the vertex array object
        glGenVertexArrays(1, &mVertexArrayObject);
        mShaderProgram.Initialize(mVertexArrayObject);
        glBindVertexArray(0);
        
    }
    
    void ProxyModel::Draw(GameTime gametime)
    {
        glBindVertexArray(mVertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
        
        mShaderProgram.Use();
        
        mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
        *(mShaderProgram.WorldViewProjection()) << wvp;
        
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        
        if (true)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else
        {
            glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
        }
        
        glBindVertexArray(0);
    }
    
}