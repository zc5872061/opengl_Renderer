//
//  BlinnPhongDemo.h
//  OglFramework
//
//  Created by Chukie on 15/10/2.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Common.h"
#include "Game.h"
#include "Camera.h"
#include "BlinnPhongEffect.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "Model.h"
#include "DrawableGameComponent.h"
#include "FontManager.h"

namespace Library {
    class BlinnPhongDemo:public DrawableGameComponent
    {
    public:
        BlinnPhongDemo(Game* game,Camera* camera);
        ~BlinnPhongDemo();
        
        virtual void Initialize();
        virtual void Update(GameTime gametime);
        virtual void Draw(GameTime gametime);
    protected:
        
        void UpdateAmbientLight(const GameTime& gameTime);
        void UpdateDirectionalLight(const GameTime& gameTime);
        void UpdateSpecularLight(const GameTime& gameTime);
        
        static const glm::vec2 LightRotationRate;
        static const float LightModulationRate;
        
        BlinnPhongEffect mShaderProgram;
        GLuint mVertexArrayObject;
        GLuint mVertexBuffer;
        GLuint mIndexBuffer;
        glm::mat4 mWorldMatrix;
        GLuint mIndexCount;
        GLuint mColorTexture;
        Light* mAmbientLight;
        DirectionLight* mDirectionalLight;
        glm::vec4 mSpecularColor;
        float mSpecularPower;
        Model* mModel;
        FontManager* mFontManager;
    };
}
