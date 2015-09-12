//
//  PointDemo.h
//  test
//
//  Created by Chukie on 15/8/31.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once

#include "DrawableGameComponent.h"

using namespace Library;

namespace Rendering
{
    class PointDemo : public DrawableGameComponent
    {
    public:
        PointDemo(Game* game, Camera* camera);
        ~PointDemo();
        
        virtual void Initialize() override;
        virtual void Draw(GameTime gametime) override;
        
    private:
        PointDemo();
        PointDemo(const PointDemo& rhs);
        PointDemo& operator=(const PointDemo& rhs);
        
        GLuint mShaderProgram;
        GLuint mVertexArrayObject;
    };
}

