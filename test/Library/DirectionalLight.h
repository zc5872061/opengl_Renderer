//
//  DirectionalLight.h
//  test
//
//  Created by Chukie on 15/9/28.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Common.h"
#include "Light.h"


namespace Library {
    class DirectionLight:public Light
    {
    public:
        DirectionLight(Game* game);
        virtual ~DirectionLight();
        
        const glm::vec3& Direction() const;
        const glm::vec3& Up() const;
        const glm::vec3& Right() const;
        void ApplyRotation(const glm::mat4& transform);
    protected:
        glm::vec3 mDirection;
        glm::vec3 mUp;
        glm::vec3 mRight;
    };
}