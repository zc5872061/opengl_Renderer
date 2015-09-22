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
#include <vector>


namespace Library {
    Model::Model(std::string modelFile)
    {
        Assimp::Importer importer;
        unsigned int flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_FlipUVs;
        const aiScene* scene = importer.ReadFile(modelFile, flags);
        
        assert(scene != nullptr);
        
        std::vector<aiMaterial*> materials;
        std::vector<aiMesh*> meshs;
        
        if (scene->HasMaterials())
        {
            for (unsigned int i = 0; i < scene->mNumMaterials; i++)
            {
                materials.push_back(scene->mMaterials[i]);
            }
        }
        
        if(scene->HasMeshes())
        {
            for(unsigned int i = 0; i < scene->mNumMeshes; i++)
            {
                aiMesh* tempMesh = scene->mMeshes[i];
                meshs.push_back(scene->mMeshes[i]);
            }
        }
        
        
    }
    
    Model::~Model()
    {
        
    }
}