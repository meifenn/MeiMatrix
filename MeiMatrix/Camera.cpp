#include "Camera.hpp"

glm::mat4 Camera::getView(glm::vec3 pos, glm::vec3 center) {
    return glm::lookAt(pos, center, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getProjection(float aspect) {
    return glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
}