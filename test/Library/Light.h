//
//  Light.h
//  test
//
//  Created by Chukie on 15/9/28.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//
#include "Common.h"
#include "GameComponent.h"

using namespace glm;

namespace Library {
    class Light:public GameComponent
    {
    public:
        Light(Game* game);
        ~Light();
        
        void SetColor(float r, float g, float b, float a);
        void SetColor(const glm::vec4& color);
        const vec4& Color() const {return mColor;}
    protected:
        vec4 mColor;
    };
}