//
//  BasicEffect.h
//  test
//
//  Created by Chukie on 15/9/12.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#pragma once
#include "Common.h"
#include "ShaderProgram.h"
#include "VertexDeclarations.h"

namespace Library {
    class BasicEffect:public ShaderProgram
    {
        SHADER_VARIABLE_DECLARATION(WorldViewProjection)
    public:
        BasicEffect();
        ~BasicEffect();
        
    };
}
