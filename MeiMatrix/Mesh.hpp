#ifndef MESH_HPP
#define MESH_HPP
#include <GL/glew.h>

class Mesh {
public:
    GLuint VAO, VBO, EBO;
    Mesh();
    void draw();
};
#endif