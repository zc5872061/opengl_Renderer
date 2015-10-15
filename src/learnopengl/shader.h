#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <vector>

class Shader
{
public:
    GLuint Program;
    // Constructor generates the shader on the fly
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr)
    {
        std::vector<char> vShaderSource;
        LoadBinaryFile(vertexPath, vShaderSource);
        const GLchar* vsourcePointer = &vShaderSource[0];
        GLint vlength = (GLint)vShaderSource.size();
        
        std::vector<char> fShaderSource;
        LoadBinaryFile(fragmentPath, fShaderSource);
        const GLchar* fsourcePointer = &fShaderSource[0];
        GLint flength = (GLint)fShaderSource.size();
        
        
        // 2. Compile shaders
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];
        // Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vsourcePointer, &vlength);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fsourcePointer, &flength);
        glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// If geometry shader is given, compile geometry shader
		GLuint geometry;
		if(geometryPath != nullptr)
		{
//			const GLchar * gShaderCode = geometryCode.c_str();
//			geometry = glCreateShader(GL_GEOMETRY_SHADER);
//			glShaderSource(geometry, 1, &gShaderCode, NULL);
//			glCompileShader(geometry);
//			checkCompileErrors(geometry, "GEOMETRY");
		}
        // Shader Program
        this->Program = glCreateProgram();
        glAttachShader(this->Program, vertex);
        glAttachShader(this->Program, fragment);
		//if(geometryPath != nullptr)
			//glAttachShader(this->Program, geometry);
        glLinkProgram(this->Program);
        checkCompileErrors(this->Program, "PROGRAM");
        // Delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
		//if(geometryPath != nullptr)
		//	glDeleteShader(geometry);

    }
    
    void LoadBinaryFile(const std::string& filename, std::vector<char>& data)
    {
        std::ifstream file = std::ifstream(filename.c_str(), std::ios::binary);
        
        if (file.bad())
        {
            assert(false);
        }
        
        file.seekg(0, std::ios::end);
        unsigned int size = (unsigned int)file.tellg();
        
        if (size > 0)
        {
            data.resize(size);
            file.seekg(0, std::ios::beg);
            file.read(&data.front(), size);
        }
        
        file.close();
        
        
    }

    
    // Uses the current shader
    void Use() { glUseProgram(this->Program); }

private:
    void checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if(type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if(!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "| ERROR::::SHADER-COMPILATION-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if(!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "| ERROR::::PROGRAM-LINKING-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
			}
		}
	}
};

#endif