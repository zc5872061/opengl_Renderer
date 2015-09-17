//
//  Model.cpp
//  test
//
//  Created by Chukie on 15/9/15.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Model.h"
#include <assimp/include/Importer.hpp>
#include <assimp/include/scene.h>
#include <assimp/include/postprocess.h>
#include <assimp/include/cimport.h>



namespace Library {
    Model::Model(Game* game, const std::string filename, bool flipUVs)
    {
        Assimp::Importer importer;
        unsigned int flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType;
        if(flipUVs)
        {
            flags |= aiProcess_FlipUVs;
        }
        
        const aiScene* scene = importer.ReadFile(filename, flags);
        //const aiScene* scene = aiImportFile(filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
        assert(scene != nullptr);
        
        if(scene->HasMaterials())
        {
            //read materials
        }
        
        if(scene->HasMeshes())
        {
            //read meshs
        }
        
        
    }
    
    Model::~Model()
    {
        
    }
}