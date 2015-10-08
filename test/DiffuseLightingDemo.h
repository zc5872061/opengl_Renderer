//
//  DiffuseLightingDemo.h
//  test
//
//  Created by Chukie on 15/9/28.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Common.h"
#include "DrawableGameComponent.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Light.h"
#include "DirectionalLight.h"

using namespace Library;

namespace Library {
    class DiffuseLightingDemo:public DrawableGameComponent
    {
    public:
        DiffuseLightingDemo(Game* game,Camera* camera);
        ~DiffuseLightingDemo();
        
        virtual void Initialize();
        virtual void Update(GameTime gametime);
        virtual void Draw(GameTime gametime);
    protected:
        enum VertexAttribute
        {
            VertexAttributePosition = 0,
            VertexAttributeTextureCoordinate = 1,
            VertexAttributeNormal = 2
        };
        
        void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer);
        void UpdateAmbientLight(const GameTime& gameTime);
        void UpdateDirectionalLight(const GameTime& gameTime);
        
        static const glm::vec2 LightRotationRate;
        
        ShaderProgram mShaderProgram;
        GLuint mVertexArrayObject;
        GLuint mVertexBuffer;
        GLuint mIndexBuffer;
        GLint mWorldViewProjectionLocation;
        GLint mWorldLocation;
        GLint mAmbientColorLocation;
        GLint mLightColorLocation;
        GLint mLightDirectionLocation;
        glm::mat4 mWorldMatrix;
        GLuint mIndexCount;
        GLuint mColorTexture;
        Light* mAmbientLight;
        DirectionLight* mDirectionLight;
        
        Model* mModel;
    };
}