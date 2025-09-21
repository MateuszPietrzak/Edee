#ifndef SHADER_H_
#define SHADER_H_

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader();

    void load(const std::string& vertexPath, const std::string& fragmentPath);
    void use();

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, glm::vec3 value) const;
    void setMat4(const std::string& name, glm::mat4 value) const;
private:
    unsigned int id;
};

#endif // SHADER_H_
