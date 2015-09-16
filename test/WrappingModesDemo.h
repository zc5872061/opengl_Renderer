//
//  WrappingModesDemo.h
//  test
//
//  Created by Chukie on 15/9/16.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#pragma once
#include "Common.h"
#include "DrawableGameComponent.h"
#include "VertexDeclarations.h"
#include "ShaderProgram.h"

using namespace Library;

namespace Rendering {
    class WrappingModesDemo:public DrawableGameComponent
    {
    public:
        WrappingModesDemo(Game* game, Camera* camera);
        ~WrappingModesDemo();
        virtual void Initialize() override;
        virtual void Draw(GameTime gametime) override;
    private:
        enum VertexAttribute
        {
            VertexAttributePosition = 0,
            VertexAttributeTextureCoordinate = 1
        };
        
        
        enum WrappingMode
        {
            WrappingModeRepeat = 0,
            WrappingModeMirroredRepeat,
            WrappingModeClampToEdge,
            WrappingModeClampToBorder,
            WrappingModeEnd
        };
        
        void CreateVertexBuffer(VertexPositionTexture* vertices, GLuint vertexCount, GLuint& vertexBuffer);
        void CreateIndexBuffer(unsigned int* indices, GLuint indexCount, GLuint& indexBuffer);
        void OnKey(int key, int scancode, int action, int mods);
        
        ShaderProgram* mShaderProgram;
        GLuint mVertexArrayObject;
        GLuint mVertexBuffer;
        GLuint mIndexBuffer;
        GLuint mWorldViewProjectionLocation;
        glm::mat4 mWorldMatrix;
        GLuint mIndexCount;
        GLuint mColorTexture;
        std::vector<GLuint> mTextureSamplers;
        std::map<WrappingMode, GLuint> mTextureSamplersByWrappingMode;
        WrappingMode mActiveWrappingMode;
    };
}
