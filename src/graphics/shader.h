#ifndef FPS_SHADER_H
#define FPS_SHADER_H

#include <string>
#include <glm/glm.hpp>

namespace FPS
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();

        void use() const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setFloat(const std::string& name, float value) const;

    private:
        unsigned int ID;
        unsigned int compileShader(unsigned int type, const std::string& source);
    };
}

#endif
