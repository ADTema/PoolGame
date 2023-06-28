#include "../headers/Camera.h"


glm::mat4 Camera::getViewMatrix() {
    return glm::inverse(getTransform() - glm::mat4(
                                             0, 0, 0, 0,
                                             0, 0, 0, 0,
                                             0, 0, 0, 0,
                                             m_width2, m_height2, 0,0));
}
Camera::Camera(float width, float height)
    : m_width2(width / 2), m_height2(height / 2) {
}
