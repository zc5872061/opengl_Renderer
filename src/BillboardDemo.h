//
//  BillboardDemo.h
//  OglRenderer
//
//  Created by Chukie on 15/10/12.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once

#include "Common.h"
#include "DrawableGameComponent.h"
#include "VertexDeclarations.h"
#include "BillboardEffect.h"

using namespace Library;

namespace Rendering {
    class BillboardDemo:public DrawableGameComponent
    {
    public:
        BillboardDemo(Game* game, Camera* camera);
        ~BillboardDemo();
        virtual void Initialize() override;
        virtual void Draw(GameTime gametime) override;
    protected:
        BillboardEffect* mShaderProgram;
        
        GLuint mVertexArrayObject;
        GLuint mVertexBuffer;
        GLuint mTexture;
    };
}