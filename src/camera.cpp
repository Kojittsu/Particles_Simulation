#include "camera.h"

void Camera::configurePerspective(const double aspectRatio) {
    gluPerspective(fov_, aspectRatio, minRenderDistance_, maxRenderDistance_);
}

void Camera::update() {
    glLoadIdentity();
    glm::vec3 cameraTarget = position_ + front_;
    gluLookAt(
        position_.x, position_.y, position_.z,
        cameraTarget.x, cameraTarget.y, cameraTarget.z,
        up_.x, up_.y, up_.z
    );
}

void Camera::computeNewPosition(const std::array<bool, 1024>& keyStates, const float deltaTime) {
    float velocity = speed_ * deltaTime;

    if (keyStates[GLFW_KEY_W]) {
        position_ += front_ * velocity;
    }
    if (keyStates[GLFW_KEY_S]) {
        position_ -= front_ * velocity;
    }
    if (keyStates[GLFW_KEY_A]) {
        position_ -= right_ * velocity;
    }
    if (keyStates[GLFW_KEY_D]) {
        position_ += right_ * velocity;
    }
    if (keyStates[GLFW_KEY_SPACE]) {
        position_ += up_ * velocity;
    }
    if (keyStates[GLFW_KEY_LEFT_SHIFT]) {
        position_ -= up_ * velocity;
    }
}

void Camera::computeNewOrientation(const double xOffset, const double yOffset) {

    azimuth_ += xOffset * sensitivity_;
    elevation_ += yOffset * sensitivity_;

    if (elevation_ > 89.0f) elevation_ = 89.0f;
    if (elevation_ < -89.0f) elevation_ = -89.0f;

    float azimuthRad = glm::radians(azimuth_);
    float elevationRad = glm::radians(elevation_);

    front_ = glm::normalize(glm::vec3(
        cos(elevationRad) * cos(azimuthRad),
        sin(elevationRad),
        cos(elevationRad) * sin(azimuthRad)
    ));

    right_ = glm::normalize(glm::cross(front_, up_));
}

void Camera::reset() {
    *this = Camera();
}

void Camera::setPosition(const glm::vec3& position) {
    position_ = position;
}

void Camera::setSpeed(const float& speed) {
    speed_ = speed;
}
