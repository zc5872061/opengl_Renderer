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
            
            mVertics.push_back(glm::vec3(v.x,v.y,v.z));
        }
        
        //Normals
        if(mesh.HasNormals())
        {
            mNormals.reserve(mesh.mNumVertices);
            for(unsigned int i = 0; i < mesh.mNumVertices; i++)
            {
                aiVector3D n = mesh.mNormals[i];
                std::cout<<"vertics normals:"<< n.x << " " << n.y << " " << n.z <<std::endl;
                mNormals.push_back(glm::vec3(n.x,n.y,n.z));
                
            }
        }
        
        // Tangents and Binormals
        if(mesh.HasTangentsAndBitangents())
        {
            mTangents.reserve(mesh.mNumVertices);
            mBiNormals.reserve(mesh.mNumVertices);
            
            for(unsigned int i = 0; i < mesh.mNumVertices; i++)
            {
                aiVector3D t = mesh.mTangents[i];
                aiVector3D b = mesh.mBitangents[i];
                
                mTangents.push_back(glm::vec3(t.x,t.y,t.z));
                mBiNormals.push_back(glm::vec3(b.x,b.y,b.z));
            }
        }
        
        // Texture Coordinates
        //unsigned int uvChannelCount = mesh.GetNumUVChannels();
        
    }
    
    void Mesh::CreateIndexBuffer(GLuint& indexBuffer)
    {
        glGenBuffers(1,&indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int) * mIndices.size(),&mIndices[0],GL_STATIC_DRAW);
    }
}