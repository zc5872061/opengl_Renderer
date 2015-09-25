//
//  SkyBox.h
//  test
//
//  Created by Chukie on 15/9/25.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Common.h"
#include "DrawableGameComponent.h"
#include "BasicEffect.h"
#include "Model.h"

using namespace glm;

namespace Library {
    class SkyBox:public DrawableGameComponent
    {
    public:
        SkyBox(
               Game* game,
               Camera* camera,
               const std::string& posXFilename,
               const std::string& negXFilename,
               const std::string& posYFilename,
               const std::string& negYFilename,
               const std::string& posZFilename,
               const std::string& negZFilename,
               float scale
               );
        ~SkyBox();
        
        virtual void Initialize();
        virtual void Update(GameTime gametime);
        virtual void Draw(GameTime gametime);
    protected:
        std::string mPosXFilename;
        std::string mNegXFilename;
        std::string mPosYFilename;
        std::string mNegYFilename;
        std::string mPosZFilename;
        std::string mNegZFilename;
        
        BasicEffect mShaderProgram;
        GLuint mVertexArrayObject;
        GLuint mVertexBuffer;
        GLuint mIndexBuffer;
        unsigned int mIndexCount;
        GLuint mSkyboxTexture;
        mat4 mWorldMatrix;
        mat4 mScaleMatrix;
        GLuint mSkyboxTextureSampler;
        
        Model* mModel;
    };
}