//
//  ModelDemo.h
//  
//
//  Created by Chukie on 15/9/23.
//
//

#pragma once

#include "DrawableGameComponent.h"
#include "BasicEffect.h"

using namespace Library;

namespace Rendering {
    class ModelDemo:public DrawableGameComponent
    {
    public:
        ModelDemo();
        ~ModelDemo();
        
        virtual void Initialize();
        virtual void Update(GameTime gametime);
        virtual void Draw(GameTime gametime);
    };
}
