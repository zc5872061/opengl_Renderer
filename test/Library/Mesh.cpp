//
//  Mesh.cpp
//  test
//
//  Created by Chukie on 15/9/14.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Mesh.h"
#include "Model.h"
#include <assimp/include/scene.h>

using namespace Library;

namespace Library {
    Mesh::Mesh(Model& model,aiMesh& mesh):
        mModel(model),
        mMaterial(nullptr),
        mName(mesh.mName.C_Str()),
        mVertics(),
        mNormals(),
        mTangents(),
        mBiNormals(),
        mTextureCoordinates(),
        mVertexColors(),
        mFaceCount(0),
        mIndices()
    {
        //mMaterial = mModel.Materials().at(mesh.mMaterialIndex);
        
        //Vertices
        mVertics.reserve(mesh.mNumVertices);
        for(unsigned int i = 0; i < mesh.mNumVertices; i++)
        {
            aiVector3D v = mesh.mVertices[i];
            std::cout<<"vertics:"<< v.x << " " << v.y << " " << v.z <<std::endl;
            mVertics.push_back(glm::vec3(v.x,v.y,v.z));
        }
    }
}