//
//  testDemo.h
//  OglRenderer
//
//  Created by Chukie on 15/10/13.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once

#include "DrawableGameComponent.h"

using namespace Library;

namespace Rendering
{
    class testDemo : public DrawableGameComponent
    {
    public:
        testDemo(Game* game, Camera* camera);
        ~testDemo();
        
        virtual void Initialize() override;
        virtual void Draw(GameTime gametime) override;
        
    private:
        testDemo();
        testDemo(const testDemo& rhs);
        testDemo& operator=(const testDemo& rhs);
        
        GLuint mShaderProgram;
        GLuint VBO;
    };
}
