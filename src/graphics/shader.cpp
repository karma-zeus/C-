#include "shader.h"
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace FPS
{
    Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
    {
        unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexSource);
        unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        int success;
        char infoLog[512];
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, nullptr, infoLog);
            std::cerr << "Shader linking failed: " << infoLog << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    Shader::~Shader()
    {
        glDeleteProgram(ID);
    }

    void Shader::use() const
    {
        glUseProgram(ID);
    }

    void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
    {
        GLint loc = glGetUniformLocation(ID, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
    }

    void Shader::setVec3(const std::string& name, const glm::vec3& value) const
    {
        GLint loc = glGetUniformLocation(ID, name.c_str());
        glUniform3f(loc, value.x, value.y, value.z);
    }

    void Shader::setFloat(const std::string& name, float value) const
    {
        GLint loc = glGetUniformLocation(ID, name.c_str());
        glUniform1f(loc, value);
    }

    unsigned int Shader::compileShader(unsigned int type, const std::string& source)
    {
        unsigned int shader = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "Shader compilation failed: " << infoLog << std::endl;
        }

        return shader;
    }
}
