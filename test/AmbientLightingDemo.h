//
//  AmbientLightingDemo.h
//  test
//
//  Created by Chukie on 15/9/28.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "DrawableGameComponent.h"
#include "Common.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Light.h"

namespace Library {
    class AmbientLightingDemo:public DrawableGameComponent
    {
    public:
        AmbientLightingDemo(Game* game,Camera* camera);
        ~AmbientLightingDemo();
        
        
        virtual void Initialize();
        virtual void Update(GameTime gametime);
        virtual void Draw(GameTime gametime);
    protected:
        enum VertexAttribute
        {
            VertexAttributePosition = 0,
            VertexAttributeTextureCoordinate = 1
        };
        
        void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer);
        void UpdateAmbientLight(const GameTime& gameTime);
        ShaderProgram mShaderProgram;
        GLuint mVertexArrayObject;
        GLuint mVertexBuffer;
        GLuint mIndexBuffer;
        GLint mWorldViewProjectionLocation;
        GLint mAmbientColorLocation;
        glm::mat4 mWorldMatrix;
        GLuint mIndexCount;
        GLuint mColorTexture;
        Light* mAmbientLight;
        Model* mModel;
    };
}

