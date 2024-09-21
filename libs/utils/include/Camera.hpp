#pragma once
#include <glm/glm.hpp>


class Camera
{
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
public:
    Camera();
    Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up);

};