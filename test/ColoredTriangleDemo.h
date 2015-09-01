//
//  ColorTriangleDemo.h
//  test
//
//  Created by Chukie on 15/9/1.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#ifndef __test__ColorTriangleDemo__
#define __test__ColorTriangleDemo__

#pragma once

#include "DrawableGameComponent.h"
#include "ShaderProgram.h"

using namespace Library;

namespace Rendering
{
    class ColoredTriangleDemo:public DrawableGameComponent
    {
    public:
        ColoredTriangleDemo(Game* game,Camera* camera);
        ~ColoredTriangleDemo();
        
        virtual void Initialize() override;
        virtual void Draw() override;
    private:
        enum VertexAttribute
        {
            VertexAttributePosition = 0,
            VertexAttributeColor = 1
        };
        ShaderProgram* mShaderProgram;
        GLuint mVertexArrayObject;
        GLuint mVertexBuffer;
    };
}

#endif /* defined(__test__ColorTriangleDemo__) */
