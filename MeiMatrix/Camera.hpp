#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::mat4 getView(glm::vec3 pos, glm::vec3 center);
    glm::mat4 getProjection(float aspect);
};
#endif