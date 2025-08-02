#ifndef SHADER_HPP
#define SHADER_HPP
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    GLuint ID;
    Shader(const char* vSrc, const char* fSrc);
    void use();
    void setMat4(const std::string& name, glm::mat4 val);
    void setFloat(const std::string& name, float val);
    void setInt(const std::string& name, int val);
    void setVec3(const std::string& name, const glm::vec3& val);

private:
    GLuint compile(GLenum type, const char* src);
};
#endif