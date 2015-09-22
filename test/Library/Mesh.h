//
//  Mesh.h
//  test
//
//  Created by Chukie on 15/9/14.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#pragma once

#include "Common.h"
#include "Model.h"

struct aiMesh;

namespace Library {
    
    class Mesh
    {
        friend class Model;
    public:
        Mesh(Model& model,aiMesh& mesh);
        
        Model& mModel;
        ModelMaterial* mMaterial;
        std::string mName;
    private:
        std::vector<glm::vec3> mVertics;
        std::vector<glm::vec3> mNormals;
        std::vector<glm::vec3> mTangents;
        std::vector<glm::vec3> mBiNormals;
        std::vector<std::vector<glm::vec3>*> mTextureCoordinates;
        std::vector<std::vector<glm::vec4>*> mVertexColors;
        unsigned int mFaceCount;
        std::vector<unsigned int> mIndices;
    };
}