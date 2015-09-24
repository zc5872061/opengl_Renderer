//
//  ModelDemo.cpp
//  
//
//  Created by Chukie on 15/9/23.
//
//

#include "ModelDemo.h"
#include "ColorHelper.h"
#include "Camera.h"


namespace Rendering {
    ModelDemo::ModelDemo(Game* game, Camera* camera):
        DrawableGameComponent(game,camera),
        mShaderProgram(),
        mVertexArrayObject(0),
        mVertexBuffer(0),
        mIndexBuffer(0),
        mWorldViewProjectionLocation(-1),
        mWorldMatrix(),
        mIndexCount(0),
        mModel(nullptr)
    {
    }
    
    ModelDemo::~ModelDemo()
    {
        glDeleteBuffers(1,&mIndexBuffer);
        glDeleteBuffers(1,&mVertexBuffer);
        glDeleteVertexArrays(1,&mVertexArrayObject);
        if(mModel)
        {
            delete mModel;
            mModel = nullptr;
        }
    }
    
    void ModelDemo::Initialize()
    {
        //build shader program
        std::vector<ShaderDefinition> shaders;
        shaders.push_back(ShaderDefinition(GL_VERTEX_SHADER,ModelDemoVStr));
        shaders.push_back(ShaderDefinition(GL_FRAGMENT_SHADER,ModelDemoFStr));
        mShaderProgram.BuildProgram(shaders);
        
       // mModel = new Model("/Users/chukie/Desktop/dragon.obj",true);
        mModel = new Model("/Users/chukie/Study/WorkWork/opengl_framework/test/resource/dragon.obj",true);
        Mesh* mesh = mModel->Meshes().at(0);
        CreateVertexBuffer(*mesh, mVertexBuffer);
        mesh->CreateIndexBuffer(mIndexBuffer);
        
        mIndexCount = (GLint)mesh->Indices().size();
        glGenVertexArrays(1,&mVertexArrayObject);
        glBindVertexArray(mVertexArrayObject);
        
        glVertexAttribPointer(VertexAttributePosition,4,GL_FLOAT,GL_FALSE,sizeof(VertexPositionColor),(void*)offsetof(VertexPositionColor, Position));
        glEnableVertexAttribArray(VertexAttributePosition);
        glVertexAttribPointer(VertexAttributeColor, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), (void*)offsetof(VertexPositionColor, Color));
        glEnableVertexAttribArray(VertexAttributeColor);
        glBindVertexArray(0);
        mWorldViewProjectionLocation = glGetUniformLocation(mShaderProgram.Program(), "WorldViewProjection");
        assert(mWorldViewProjectionLocation != -1);
    }
    
    void ModelDemo::Update(GameTime gametime)
    {
        
    }
    
    void ModelDemo::Draw(GameTime gametime)
    {
        glBindVertexArray(mVertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER,mVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mIndexBuffer);
        
        mShaderProgram.Use();
        mat4 wvp = mCamera->ViewProjectionMatrix() * mWorldMatrix;
        glUniformMatrix4fv(mWorldViewProjectionLocation, 1, GL_FALSE, &wvp[0][0]);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        
        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
    }
    
    void ModelDemo::CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer)
    {
        const std::vector<vec3>& sourceVertices = mesh.Vertices();
        std::vector<VertexPositionColor> vertices;
        
        vertices.reserve(sourceVertices.size());
        
        if(mesh.VertexColors().size() > 0)
        {
            std::vector<vec4>* vertexColors = mesh.VertexColors().at(0);
            assert(vertexColors->size() == sourceVertices.size());
            
            for(unsigned int i = 0; i < sourceVertices.size(); i++)
            {
                vec3 position = sourceVertices.at(i);
                vec4 color = vertexColors->at(i);
                vertices.push_back(VertexPositionColor(vec4(position.x,position.y,position.z,1.0),color));
            }
        }
        else
        {
            for(unsigned int i = 0; i < sourceVertices.size(); i++)
            {
                vec3 position = sourceVertices.at(i);
                vec4 color = ColorHelper::RandomColor();
                vertices.push_back(VertexPositionColor(vec4(position.x,position.y,position.z,1.0),color));
            }
        }
        
        glGenBuffers(1,&vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER,sizeof(VertexPositionColor)*vertices.size(),&vertices[0],GL_STATIC_DRAW);
        
    }
}