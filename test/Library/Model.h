//
//  Model.h
//  test
//
//  Created by Chukie on 15/9/15.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once

#include "Common.h"

namespace Library {
    
    class Game;
    class Mesh;
    class ModelMaterial;
    class AnimationClip;
    
    class Model
    {
        Model(Game* game, const std::string filename, bool flipUVs = false);
        ~Model();
        
        
    };
}
