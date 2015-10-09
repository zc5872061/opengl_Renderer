//
//  BlinnPhongDemo.cpp
//  OglFramework
//
//  Created by Chukie on 15/10/2.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "BlinnPhongDemo.h"
#include "ColorHelper.h"
#include "VectorHelper.h"
#include <glm/glm/gtx/transform.hpp>
#include <soil/SOIL.h>

using namespace Library;

namespace Library {
    
    const vec2 BlinnPhongDemo::LightRotationRate = vec2(360.0f, 360.0f);
    const float BlinnPhongDemo::LightModulationRate = UCHAR_MAX;
    
    BlinnPhongDemo::BlinnPhongDemo(Game* game,Camera* camera):
    DrawableGameComponent(game,camera),
    mShaderProgram(),
    mVertexArrayObject(0),
    mVertexBuffer(0),
    mIndexBuffer(0),
    mWorldMatrix(),
    mIndexCount(0),
    mColorTexture(0),
    mAmbientLight(nullptr),
    mDirectionalLight(nullptr),
    mSpecularColor(ColorHelper::White),
    mSpecularPower(25.0),
    mModel(nullptr)
    {
        
    }
    
    BlinnPhongDemo::~BlinnPhongDemo()
    {
        DeleteObject(mAmbientLight);
        DeleteObject(mDirectionalLight);
        DeleteObject(mModel);
        glDeleteTextures(1, &mColorTexture);
        glDeleteBuffers(1,&mVertexBuffer);
        glDeleteBuffers(1,&mIndexBuffer);
        glDeleteVertexArrays(1,&mVertexArrayObject);
    }
    
    void BlinnPhongDemo::Initialize()
    {
        //build shaders
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,BlinnPhongVStr));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,BlinnPhongFStr));
        mShaderProgram.BuildProgram(shaders);
        
        mModel = new Model(dragonModel,true);
        Mesh* mesh = mModel->Meshes().at(0);
        mShaderProgram.createVertexBuffer(*mesh, mVertexBuffer);
        mesh->CreateIndexBuffer(mIndexBuffer);
        mIndexCount = (GLuint)mesh->Indices().size();
        
        // Load the texture
        mColorTexture = SOIL_load_OGL_texture(earthImgStr, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
        assert(mColorTexture !=0);
        // Create the vertex array object
        glGenVertexArrays(1, &mVertexArrayObject);
        mShaderProgram.Initialize(mVertexArrayObject);
        glBindVertexArray(0);
        
        mAmbientLight = new Light(mGame);
        mAmbientLight->SetColor(ColorHelper::Black);
        
        mDirectionalLight = new DirectionLight(mGame);
    }
    
    void BlinnPhongDemo::Update(GameTime gametime)
    {
        UpdateAmbientLight(gametime);
        UpdateDirectionalLight(gametime);
        UpdateSpecularLight(gametime);
    }
    
    void BlinnPhongDemo::Draw(GameTime gametime)
    {
        glBindVertexArray(mVertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
        mShaderProgram.Use();
        
        mWorldMatrix = mat4();
        mat4 mScaleMatrix = glm::scale(mat4(), vec3(1,1,1));
        mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix*mScaleMatrix;
        *(mShaderProgram.WorldViewProjection()) << wvp;
        *(mShaderProgram.World()) << mWorldMatrix;
        *mShaderProgram.AmbientColor() << mAmbientLight->Color();
        *mShaderProgram.LightColor() << mDirectionalLight->Color();
        *mShaderProgram.LightDirection() << mDirectionalLight->Direction();
        *mShaderProgram.CameraPosition() << mCamera->Position();
        *mShaderProgram.SpecularColor() << mSpecularColor;
        *mShaderProgram.SpecularPower() << mSpecularPower;
        
        glBindTexture(GL_TEXTURE_2D, mColorTexture);
        
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        
        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
        
        glBindVertexArray(mVertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
        mShaderProgram.Use();
        
        
        vec4 m4 = mWorldMatrix[3];
        

        m4.y = -2;
        
        mWorldMatrix[3] = m4;
        
        
        mScaleMatrix = glm::scale(mat4(), vec3(1,-1,1));
        wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix*mScaleMatrix;
        *(mShaderProgram.WorldViewProjection()) << wvp;
        *(mShaderProgram.World()) << mWorldMatrix;
        *mShaderProgram.AmbientColor() << mAmbientLight->Color();
        *mShaderProgram.LightColor() << mDirectionalLight->Color();
        *mShaderProgram.LightDirection() << mDirectionalLight->Direction();
        *mShaderProgram.CameraPosition() << mCamera->Position();
        *mShaderProgram.SpecularColor() << mSpecularColor;
        *mShaderProgram.SpecularPower() << mSpecularPower;
        
        glBindTexture(GL_TEXTURE_2D, mColorTexture);
        
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        
        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
        
    }
    
    void BlinnPhongDemo::UpdateAmbientLight(const GameTime& gameTime)
    {
        static float ambientIntensity = 0.0f;
        
        if (glfwGetKey(mGame->Window(), GLFW_KEY_R) && ambientIntensity < 1.0f)
        {
            ambientIntensity += (float)gameTime.ElapsedGameTime();
            ambientIntensity = glm::min(ambientIntensity, 1.0f);
            
            mAmbientLight->SetColor(vec4((vec3)ambientIntensity, 1.0f));
        }
        
        if (glfwGetKey(mGame->Window(), GLFW_KEY_F) && ambientIntensity > 0.0f)
        {
            ambientIntensity -= (float)gameTime.ElapsedGameTime();
            ambientIntensity = glm::max(ambientIntensity, 0.0f);
            
            mAmbientLight->SetColor(vec4((vec3)ambientIntensity, 1.0f));
        }
    }
    
    void BlinnPhongDemo::UpdateDirectionalLight(const GameTime& gameTime)
    {
        static float directionalIntensity = 1.0f;
        float elapsedTime = (float)gameTime.ElapsedGameTime();
        
        // Upddate directional light intensity
        if (glfwGetKey(mGame->Window(), GLFW_KEY_T) && directionalIntensity < 1.0f)
        {
            directionalIntensity += elapsedTime;
            directionalIntensity = glm::min(directionalIntensity, 1.0f);
            
            mDirectionalLight->SetColor(vec4((vec3)directionalIntensity, 1.0f));
        }
        if (glfwGetKey(mGame->Window(), GLFW_KEY_G) && directionalIntensity > 0.0f)
        {
            directionalIntensity -= elapsedTime;
            directionalIntensity = glm::max(directionalIntensity, 0.0f);
            
            mDirectionalLight->SetColor(vec4((vec3)directionalIntensity, 1.0f));
        }
        
        // Rotate directional light
        vec2 rotationAmount = Vector2Helper::Zero;
        if (glfwGetKey(mGame->Window(), GLFW_KEY_LEFT))
        {
            rotationAmount.x += LightRotationRate.x * elapsedTime;
        }
        if (glfwGetKey(mGame->Window(), GLFW_KEY_RIGHT))
        {
            rotationAmount.x -= LightRotationRate.x * elapsedTime;
        }
        if (glfwGetKey(mGame->Window(), GLFW_KEY_UP))
        {
            rotationAmount.y += LightRotationRate.y * elapsedTime;
        }
        if (glfwGetKey(mGame->Window(), GLFW_KEY_DOWN))
        {
            rotationAmount.y -= LightRotationRate.y * elapsedTime;
        }
        
        mat4 lightRotationMatrix;
        if (rotationAmount.x != 0)
        {
            lightRotationMatrix = glm::rotate(mat4(), rotationAmount.x, Vector3Helper::Up);
        }
        
        if (rotationAmount.y != 0)
        {
            lightRotationMatrix = rotate(lightRotationMatrix, rotationAmount.y, mDirectionalLight->Right());
        }
        
        if (rotationAmount.x != 0.0f || rotationAmount.y != 0.0f)
        {
            mDirectionalLight->ApplyRotation(lightRotationMatrix);
            //mProxyModel->ApplyRotation(lightRotationMatrix);
        }
    }
    
    void BlinnPhongDemo::UpdateSpecularLight(const GameTime& gameTime)
    {
        static float specularIntensity = 1.0f;
        
        if (glfwGetKey(mGame->Window(), GLFW_KEY_Y) && specularIntensity < 1.0f)
        {
            specularIntensity += (float)gameTime.ElapsedGameTime();
            specularIntensity = glm::min(specularIntensity, 1.0f);
            
            mSpecularColor = (vec4((vec3)specularIntensity, 1.0f));
        }
        
        if (glfwGetKey(mGame->Window(), GLFW_KEY_H) && specularIntensity > 0.0f)
        {
            specularIntensity -= (float)gameTime.ElapsedGameTime();
            specularIntensity = glm::max(specularIntensity, 0.0f);
            
            mSpecularColor = (vec4((vec3)specularIntensity, 1.0f));
        }
        
        static float specularPower = mSpecularPower;
        
        if (glfwGetKey(mGame->Window(), GLFW_KEY_U) && specularPower < UCHAR_MAX)
        {
            specularPower += LightModulationRate * (float)gameTime.ElapsedGameTime();
            specularPower = glm::min(specularPower, static_cast<float>(UCHAR_MAX));
            
            mSpecularPower = specularPower;
        }
        
        if (glfwGetKey(mGame->Window(), GLFW_KEY_J) && specularPower > 0.0f)
        {
            specularPower -= LightModulationRate * (float)gameTime.ElapsedGameTime();
            specularPower = glm::max(specularPower, 0.0f);
            
            mSpecularPower = specularPower;
        }
    }
}