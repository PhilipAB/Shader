#include "Camera.h"

Camera::Camera(float width, float height, float aperture, float min_distance, float max_distance) {
    camera_width = width;
    camera_height = height;
    camera_aperture = aperture;
    camera_min_dist = min_distance;
    camera_max_dist = max_distance;
}

Camera::Camera(float width, float height, float aperture, float min_dist, float max_dist, Transform* target) {
    camera_width = width;
    camera_height = height;
    camera_aperture = aperture;
    camera_min_dist = min_dist;
    camera_max_dist = max_dist;
    m_target = target;
}

Camera::~Camera() {

}

glm::mat4 Camera::getViewMatrix() {
    glm::vec3 position = getPosition();
    if(m_target != nullptr) {
        if (this->getParent() != nullptr) {
            position = position + this->getParent()->getPosition();
        }
        glm::vec3 targetPos = m_target->getPosition();
        return glm::lookAt(glm::vec3(position.x, position.y, position.z), targetPos, getYAxis());
    } else {
        return glm::inverse(getMatrix());
    }
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(camera_aperture, (camera_width/camera_height), camera_min_dist, camera_max_dist);
}

void Camera::bind(ShaderProgram *shader) {
    shader->setUniform("view_matrix", getViewMatrix(), false);
    shader->setUniform("projection_matrix", getProjectionMatrix(), false);
}

