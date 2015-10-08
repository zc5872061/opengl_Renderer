//
//  ProxyModel.h
//  OglFramework
//
//  Created by Chukie on 15/10/7.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#pragma once
#include "Common.h"
#include "DrawableGameComponent.h"
#include "BasicEffect.h"
#include "Model.h"


namespace Library {
    class ProxyModel:public DrawableGameComponent
    {
    public:
        ProxyModel(Game* game, Camera* camera);
        ~ProxyModel();
        
        virtual void Initialize() override;
        virtual void Draw(GameTime gametime) override;
        
    protected:
        std::string mModelFileName;
        BasicEffect mShaderProgram;
        GLuint mVertexArrayObject;
        GLuint mVertexBuffer;
        GLuint mIndexBuffer;
        UINT mIndexCount;
        
        Model* mModel;
        
        glm::mat4 mWorldMatrix;
        glm::mat4 mScaleMatrix;
        
    };
}