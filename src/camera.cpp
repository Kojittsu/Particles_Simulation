#include "camera.h"

Camera::Camera(const glm::vec3& position,
    const glm::vec3& front,
    const glm::vec3& up,
    const float azimuth,
    const float elevation,
    const float speed,
    const float fov,
    const float minRenderDistance,
    const float maxRenderDistance
    ):
        m_position(position),
        m_front(front),
        m_up(up),
        m_azimuth(azimuth),
        m_elevation(elevation),
        m_speed(speed),
        m_fov(fov),
        m_minRenderDistance(minRenderDistance),
        m_maxRenderDistance(maxRenderDistance)
{
    m_right = glm::normalize(glm::cross(m_front, m_up));
}

void Camera::configurePerspective(double aspectRatio) {
    gluPerspective(m_fov, aspectRatio, m_minRenderDistance, m_maxRenderDistance);
}

void Camera::update() {
    glLoadIdentity();
    glm::vec3 cameraTarget = m_position + m_front;
    gluLookAt(
        m_position.x, m_position.y, m_position.z,
        cameraTarget.x, cameraTarget.y, cameraTarget.z,
        m_up.x, m_up.y, m_up.z
    );
}


void Camera::computeNewPosition(const std::array<bool, 1024>& keyStates, float deltaTime) {
    float velocity = m_speed * deltaTime;

    if (keyStates[GLFW_KEY_W]) {
        m_position += m_front * velocity;
    }
    if (keyStates[GLFW_KEY_S]) {
        m_position -= m_front * velocity;
    }
    if (keyStates[GLFW_KEY_A]) {
        m_position -= m_right * velocity;
    }
    if (keyStates[GLFW_KEY_D]) {
        m_position += m_right * velocity;
    }
    if (keyStates[GLFW_KEY_SPACE]) {
        m_position += m_up * velocity;
    }
    if (keyStates[GLFW_KEY_LEFT_SHIFT]) {
        m_position -= m_up * velocity;
    }
}

void Camera::computeNewOrientation(double xOffset, double yOffset) {
    float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    m_azimuth += xOffset;
    m_elevation += yOffset;

    if (m_elevation > 89.0f) m_elevation = 89.0f;
    if (m_elevation < -89.0f) m_elevation = -89.0f;

    float azimuthRad = glm::radians(m_azimuth);
    float elevationRad = glm::radians(m_elevation);

    m_front = glm::normalize(glm::vec3(
        cos(elevationRad) * cos(azimuthRad),
        sin(elevationRad),
        cos(elevationRad) * sin(azimuthRad)
    ));

    m_right = glm::normalize(glm::cross(m_front, m_up));
}

void Camera::setPosition(const glm::vec3& position) {
    m_position = position;
}

void Camera::setSpeed(float speed) {
    m_speed = speed;
}
