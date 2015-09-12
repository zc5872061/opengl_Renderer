//
//  DrawableGameComponent.h
//  test
//
//  Created by Chukie on 15/8/31.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#ifndef __test__DrawableGameComponent__
#define __test__DrawableGameComponent__

#pragma once

#include "Common.h"
#include "GameComponent.h"

namespace Library
{
    class Camera;
    
    class DrawableGameComponent : public GameComponent
    {
    public:
        DrawableGameComponent();
        DrawableGameComponent(Game* game);
        DrawableGameComponent(Game* game, Camera* camera);
        virtual ~DrawableGameComponent();
        
        bool Visible() const;
        void SetVisible(bool visible);
        
        Camera* GetCamera();
        void SetCamera(Camera* camera);
        
        virtual void Draw(GameTime gametime);
        
    protected:
        bool mVisible;
        Camera* mCamera;
        
    private:
        DrawableGameComponent(const DrawableGameComponent& rhs);
        DrawableGameComponent& operator=(const DrawableGameComponent& rhs);
    };
}

#endif /* defined(__test__DrawableGameComponent__) */
