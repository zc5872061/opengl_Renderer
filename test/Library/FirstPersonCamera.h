//
//  FirstPersonCamera.h
//  test
//
//  Created by Chukie on 15/8/30.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#ifndef __test__FirstPersonCamera__
#define __test__FirstPersonCamera__

#include "Camera.h"
#include "Game.h"

namespace Library
{
    class FirstPersonCamera : public Camera
    {
        
    public:
        FirstPersonCamera(Game* game);
        FirstPersonCamera(Game* game, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
        
        virtual ~FirstPersonCamera();
        
        float& MouseSensitivity();
        float& RotationRate();
        float& MovementRate();
        
        virtual void Initialize() override;
        virtual void Update(GameTime gametime) override;
        
        static const float DefaultMouseSensitivity;
        static const float DefaultRotationRate;
        static const float DefaultMovementRate;
        
    protected:
        float mMouseSensitivity;
        float mRotationRate;
        float mMovementRate;
        
    private:
        FirstPersonCamera(const FirstPersonCamera& rhs);
        FirstPersonCamera& operator=(const FirstPersonCamera& rhs);
        
        double mLastCursorX;
        double mLastCursorY;
    };
}



#endif /* defined(__test__FirstPersonCamera__) */
