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
#include "Mesh.h"

using namespace Library;
using namespace glm;

namespace Rendering {
    class ModelDemo:public DrawableGameComponent
    {
    public:
        ModelDemo(Game* game, Camera* camera);
        ~ModelDemo();
        
        virtual void Initialize();
        virtual void Update(GameTime gametime);
        virtual void Draw(GameTime gametime);
        
        void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer);
    protected:
        enum VertexAttribute
        {
            VertexAttributePosition = 0,
            VertexAttributeColor = 1
        };
        
        Model* mModel;
        ShaderProgram mShaderProgram;
        GLuint mVertexArrayObject;
        GLuint mVertexBuffer;
        GLuint mIndexBuffer;
        GLuint mWorldViewProjectionLocation;
        mat4 mWorldMatrix;
        GLuint mIndexCount;
    };
}
