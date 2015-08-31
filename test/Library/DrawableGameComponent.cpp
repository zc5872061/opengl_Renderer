//
//  DrawableGameComponent.cpp
//  test
//
//  Created by Chukie on 15/8/31.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "DrawableGameComponent.h"

namespace Library
{
    DrawableGameComponent::DrawableGameComponent()
    : GameComponent(), mVisible(true), mCamera(nullptr)
    {
        GameComponent::SetDrawAble(true);
    }
    
    DrawableGameComponent::DrawableGameComponent(Game* game)
    : GameComponent(game), mVisible(true), mCamera(nullptr)
    {
    }
    
    DrawableGameComponent::DrawableGameComponent(Game* game, Camera* camera)
    : GameComponent(game), mVisible(true), mCamera(camera)
    {
    }
    
    DrawableGameComponent::~DrawableGameComponent()
    {
    }
    
    bool DrawableGameComponent::Visible() const
    {
        return mVisible;
    }
    
    void DrawableGameComponent::SetVisible(bool visible)
    {
        mVisible = visible;
    }
    
    Camera* DrawableGameComponent::GetCamera()
    {
        return mCamera;
    }
    
    void DrawableGameComponent::SetCamera(Camera* camera)
    {
        mCamera = camera;
    }
    
    void DrawableGameComponent::Draw()
    {
    }
}
