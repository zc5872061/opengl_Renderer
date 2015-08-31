//
//  Variable.h
//  test
//
//  Created by Chukie on 15/8/30.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#ifndef __test__Variable__
#define __test__Variable__

#include "Common.h"

namespace Library {
    class ShaderProgram;
    
    class Variable
    {
    public:
        Variable(ShaderProgram* shaderProgram,const std::string& name);
        
        ShaderProgram* GetShaderProgram();
        const GLint& Location() const;
        const std::string& Name() const;
        
        Variable& operator<<(const glm::mat4& value);
        Variable& operator<<(const glm::vec4& value);
        Variable& operator<<(const glm::vec3& value);
        Variable& operator<<(const glm::vec2& value);
        Variable& operator<<(float value);
        Variable& operator<<(int value);
        
    private:
        Variable(const Variable& rhs);
        Variable& operator=(const Variable& rhs);
        
        ShaderProgram* mShaderProgram;
        GLint mLocation;
        std::string mName;
    };
}


#endif /* defined(__test__Variable__) */
