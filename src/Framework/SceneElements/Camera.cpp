#include "Camera.h"

Camera::Camera(float width, float height, float aperture, float min_dist, float max_dist) {
    camera_width = width;
    camera_height = height;
    camera_aperture = aperture;
    camera_min_dist = min_dist;
    camera_max_dist = max_dist;
}

Camera::~Camera() {

}

glm::mat4 Camera::getViewMatrix() {
    glm::vec3 position = getPosition();
    glm::vec3 direction = position - getZAxis();
    return glm::lookAt(position, direction, getYAxis());

}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(camera_aperture, (camera_width/camera_height), camera_min_dist, camera_max_dist);
}

void Camera::bind(ShaderProgram *shader) {
    shader->setUniform("view_matrix", getViewMatrix(), false);
    shader->setUniform("projection_matrix", getProjectionMatrix(), false);
}

