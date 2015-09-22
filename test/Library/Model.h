//
//  Model.h
//  test
//
//  Created by Chukie on 15/9/15.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once

#include "Common.h"

struct aiNode;

namespace Library {
    
    class Mesh;
    class ModelMaterial;
    
    class Model
    {
        friend class Mesh;
    public:
        Model(std::string modelFile,bool flipUVs);
        ~Model();
        
        const std::vector<Mesh*>& Meshes() const;
        const std::vector<ModelMaterial*>& Materials() const;
    private:
        std::vector<Mesh*> mMeshes;
        std::vector<ModelMaterial*> mMaterials;
    };
}
