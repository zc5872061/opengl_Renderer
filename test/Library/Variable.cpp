//
//  Variable.cpp
//  test
//
//  Created by Chukie on 15/8/30.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Variable.h"
#include "ShaderProgram.h"



namespace Library
{
    Variable::Variable(ShaderProgram* shaderProgram,const std::string& name)
    {
        assert(shaderProgram != nullptr && !name.empty());
        mShaderProgram = shaderProgram;
        mName = name;
        mLocation = -1;
        
        
        mLocation = glGetUniformLocation(shaderProgram->Program(),name.c_str());
        assert(mLocation != -1);
    }
    
    
    ShaderProgram* Variable::GetShaderProgram()
    {
        return mShaderProgram;
    }
    
    const GLint& Variable::Location() const
    {
        return mLocation;
    }
    
    const std::string& Variable::Name() const
    {
        return mName;
    }
    
    Variable& Variable::operator<<(const glm::mat4& value)
    {
        glUniformMatrix4fv(mLocation, 1, GL_FALSE, &value[0][0]);
        
        return *this;
    }
    
    Variable& Variable::operator<<(const glm::vec4& value)
    {
        glUniform4fv(mLocation, 1, &value[0]);
        
        return *this;
    }
    
    Variable& Variable::operator<<(const glm::vec3& value)
    {
        glUniform3fv(mLocation, 1, &value[0]);
        
        return *this;
    }
    
    Variable& Variable::operator<<(const glm::vec2& value)
    {
        glUniform2fv(mLocation, 1, &value[0]);
        
        return *this;
    }
    
    Variable& Variable::operator<<(float value)
    {
        glUniform1f(mLocation, value);
        
        return *this;
    }
    
    Variable& Variable::operator<<(int value)
    {
        glUniform1i(mLocation, value);
        
        return *this;
    }
}