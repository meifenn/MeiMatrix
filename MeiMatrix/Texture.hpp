#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <GL/glew.h>
#include <string>

class Texture {
public:
    GLuint ID;
    Texture(const char* path);
    void bind();
};
#endif