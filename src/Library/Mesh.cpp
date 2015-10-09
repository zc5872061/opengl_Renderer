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
                //std::cout<<"vertics normals:"<< n.x << " " << n.y << " " << n.z <<std::endl;
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
        
        // Vertex Colors
        unsigned int colorChannelCount = mesh.GetNumColorChannels();
        for (unsigned int i = 0; i < colorChannelCount; i++)
        {
            std::vector<glm::vec4>* vertexColors = new std::vector<glm::vec4>();
            vertexColors->reserve(mesh.mNumVertices);
            mVertexColors.push_back(vertexColors);
            
            aiColor4D* aiVertexColors = mesh.mColors[i];
            for (unsigned int j = 0; j < mesh.mNumVertices; j++)
            {
                aiColor4D c = aiVertexColors[j];
                vertexColors->push_back(glm::vec4(c.r, c.g, c.b, c.a));
            }
        }
        
        //Indexs
        if(mesh.HasFaces())
        {
            mFaceCount = mesh.mNumFaces;
            for(unsigned int i = 0; i < mFaceCount; i++)
            {
                aiFace* face = &mesh.mFaces[i];
                for(unsigned int j = 0; j < face->mNumIndices; j ++)
                {
                    int i = face->mIndices[j];
                    mIndices.push_back(face->mIndices[j]);
                }
            }
        }
        
        // Texture Coordinates
        unsigned int uvChannelCount = mesh.GetNumUVChannels();
        for (unsigned int i = 0; i < uvChannelCount; i++)
        {
            std::vector<glm::vec3>* textureCoordinates = new std::vector<glm::vec3>();
            textureCoordinates->reserve(mesh.mNumVertices);
            mTextureCoordinates.push_back(textureCoordinates);
            
            aiVector3D* aiTextureCoordinates = mesh.mTextureCoords[i];
            for (unsigned int j = 0; j < mesh.mNumVertices; j++)
            {
                aiVector3D uv = aiTextureCoordinates[j];
                textureCoordinates->push_back(glm::vec3(uv.x, uv.y, uv.z));
            }
        }
        
    }
    
    void Mesh::CreateIndexBuffer(GLuint& indexBuffer)
    {
        glGenBuffers(1,&indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int) * mIndices.size(),&mIndices[0],GL_STATIC_DRAW);
    }
}