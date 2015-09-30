//
//  DirectionalLight.cpp
//  test
//
//  Created by Chukie on 15/9/28.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "DirectionalLight.h"
#include "VectorHelper.h"


namespace Library {
    DirectionLight::DirectionLight(Game* game):
    Light(game),
    mDirection(Vector3Helper::Forward),
    mUp(Vector3Helper::Up),
    mRight(Vector3Helper::Right)
    {
        
    }
    
    DirectionLight::~DirectionLight()
    {
        
    }
    
    const glm::vec3& DirectionLight::Direction() const
    {
        return mDirection;
    }
    
    const glm::vec3& DirectionLight::Up() const
    {
        return mUp;
    }
    
    const glm::vec3& DirectionLight::Right() const
    {
        return mRight;
    }
    
    void DirectionLight::ApplyRotation(const glm::mat4& transform)
    {
        glm::vec4 direction = transform * vec4(mDirection,0.0);
        mDirection = (vec3)normalize(direction);
        
        vec4 up = transform * vec4(mUp,0.0);
        mUp = (vec3)normalize(up);
        
        mRight = cross(mDirection,mUp);
        mUp = cross(mRight, mDirection);
    }
}