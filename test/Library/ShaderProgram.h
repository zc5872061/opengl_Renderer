//
//  Shader.h
//  test
//
//  Created by Chukie on 15/8/30.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#ifndef __test__Shader__
#define __test__Shader__


#include "Common.h"
#include "Variable.h"
#include <vector>
#include <map>

namespace Library
{
    class Model;
    class Mesh;
    
    typedef std::pair<GLenum, std::wstring> ShaderDefinition;
    
    class ShaderProgram
    {
    public:
        ShaderProgram();
        virtual ~ShaderProgram();
        
        static GLuint CompileShaderFromFile(GLenum shaderType, const std::wstring& filename);
        
        Variable* operator[](const std::string& variableName);
        
        GLuint Program();
        const std::vector<Variable*>& Variables() const;
        const std::map<std::string, Variable*>& VariablesByName() const;
        
        void BuildProgram(const std::vector<ShaderDefinition>& shaderDefinitions);
        
        virtual void Initialize(GLuint vertexArrayObject);
        virtual void Use() const;
        virtual void CreateVertexBuffer(const Model& model, std::vector<GLuint>& vertexBuffers) const;
        virtual void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer) const;
        virtual unsigned int VertexSize() const;
        
    protected:
        GLuint mProgram;
        std::vector<Variable*> mVariables;
        std::map<std::string, Variable*> mVariablesByName;
        
    private:
        ShaderProgram(const ShaderProgram& rhs);
        ShaderProgram& operator=(const ShaderProgram& rhs);
    };
}



#endif /* defined(__test__Shader__) */
