//
//  Light.cpp
//  test
//
//  Created by Chukie on 15/9/28.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Light.h"
#include "ColorHelper.h"


namespace Library {
    Light::Light(Game* game):
    GameComponent(game),
    mColor(ColorHelper::White)
    {
        
    }
    
    Light::~Light()
    {
        
    }
    
    void Light::SetColor(float r, float g, float b, float a)
    {
        vec4 color(r,g,b,a);
        SetColor(color);
    }
    
    void Light::SetColor(const vec4& color)
    {
        mColor = color;
    }
}