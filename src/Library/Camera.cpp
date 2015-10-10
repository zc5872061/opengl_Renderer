//
//  Camera.cpp
//  test
//
//  Created by Chukie on 15/8/30.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Camera.h"
#include <glm/gtc/matrix_transform.inl>
#include "VectorHelper.h"
#include <iostream>

using namespace::glm;

namespace Library {
    const float Camera::DefaultFieldOfView = 45.0f;
    const float Camera::DefaultNearPlaneDistance = 0.01f;
    const float Camera::DefaultFarPlaneDistance = 1000.0f;
    
    Camera::Camera(Game* game):
        GameComponent(game),
        mFieldOfView(DefaultFieldOfView),
        mAspectRatio(static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT),
        mNearPlaneDistance(DefaultNearPlaneDistance),
        mFarPlaneDistance(DefaultFarPlaneDistance),
        mPosition(),
        mDirection(),
        mUp(),
        mRight(),
        mViewMatrix(),
        mProjectionMatrix(),
        mOrthoProjectionMatrix()
    {
    }
    
    Camera::Camera(Game* game, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance):
        GameComponent(game),
        mFieldOfView(fieldOfView),
        mAspectRatio(aspectRatio),
        mNearPlaneDistance(nearPlaneDistance),
        mFarPlaneDistance(farPlaneDistance),
        mPosition(),
        mDirection(),
        mUp(),
        mRight(),
        mViewMatrix(),
        mProjectionMatrix(),
        mOrthoProjectionMatrix()
    {
        
    }
    
    Camera::~Camera()
    {
    }
    
    const glm::vec3& Camera::Position() const
    {
        return mPosition;
    }
    
    const glm::vec3& Camera::Direction() const
    {
        return mDirection;
    }
    
    const glm::vec3& Camera::Up() const
    {
        return mUp;
    }
    
    const glm::vec3& Camera::Right() const
    {
        return mRight;
    }
    
    float Camera::AspectRatio() const
    {
        return mAspectRatio;
    }
    
    float Camera::FieldOfView() const
    {
        return mFieldOfView;
    }
    
    float Camera::NearPlaneDistance() const
    {
        return mNearPlaneDistance;
    }
    
    float Camera::FarPlaneDistance() const
    {
        return mFarPlaneDistance;
    }
    
    const glm::mat4& Camera::ViewMatrix() const
    {
        return mViewMatrix;
    }
    
    const glm::mat4&Camera::ProjectionMatrix() const
    {
        return mProjectionMatrix;
    }
    
    glm::mat4 Camera::ViewProjectionMatrixOrth()
    {
        glm::vec3 target = vec3(0) + Vector3Helper::Forward;
        glm::mat4 viewMatrix = lookAt(vec3(0), target, Vector3Helper::Up);
        return mOrthoProjectionMatrix * viewMatrix;
    }
    
    glm::mat4 Camera::ViewProjectionMatrix() const
    {
        return mProjectionMatrix * mViewMatrix;
    }
    
    void Camera::SetPosition(float x, float y, float z)
    {
        mPosition = glm::vec3(x, y, z);
    }
    
    void Camera::SetPosition(const glm::vec3& position)
    {
        mPosition = position;
    }
    
    void Camera::Reset()
    {
        mPosition = Vector3Helper::Zero;
        mDirection = Vector3Helper::Forward;
        mUp = Vector3Helper::Up;
        mRight = Vector3Helper::Right;
        
        UpdateViewMatrix();
    }
    
    void Camera::Initialize()
    {
        UpdateProjectionMatrix();
        UpdateOrthProjectionMatrix();
        Reset();
    }
    
    void Camera::Update(GameTime gametime)
    {
        UpdateViewMatrix();
    }
    
    void Camera::UpdateViewMatrix()
    {
        glm::vec3 target = mPosition + mDirection;
        mViewMatrix = lookAt(mPosition, target, mUp);
    }
    
    void Camera::UpdateProjectionMatrix()
    {
        mProjectionMatrix = perspective(mFieldOfView, mAspectRatio, mNearPlaneDistance, mFarPlaneDistance);
    }
    
    void Camera::UpdateOrthProjectionMatrix()
    {
        mOrthoProjectionMatrix = glm::ortho(0.0f, static_cast<GLfloat>(SCREEN_WIDTH), 0.0f, static_cast<GLfloat>(SCREEN_HEIGHT));
    }
    
    void Camera::ApplyRotation(const glm::mat4& transform)
    {
        vec4 direction = transform * vec4(mDirection, 0.0f);
        mDirection = (vec3)normalize(direction);
        
        vec4 up	= transform * vec4(mUp, 0.0f);
        mUp = (vec3)normalize(up);
        
        mRight = cross(mDirection, mUp);
        mUp = cross(mRight, mDirection);
    }
}
