#include "Shader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Shader::Shader(const char* vSrc, const char* fSrc) {
    GLuint v = compile(GL_VERTEX_SHADER, vSrc);
    GLuint f = compile(GL_FRAGMENT_SHADER, fSrc);
    ID = glCreateProgram();
    glAttachShader(ID, v);
    glAttachShader(ID, f);
    glLinkProgram(ID);
    glDeleteShader(v);
    glDeleteShader(f);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setMat4(const std::string& name, glm::mat4 val) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setFloat(const std::string& name, float val) {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), val);
}

void Shader::setInt(const std::string& name, int val) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
}

void Shader::setVec3(const std::string& name, const glm::vec3& val) {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(val));
}

GLuint Shader::compile(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
}
