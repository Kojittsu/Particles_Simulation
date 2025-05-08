#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp> // For mathematics Opengl
#include <GL/glu.h>  // For gluPerspective
#include <GLFW/glfw3.h>
#include "array.h"

class Camera {
public:
    Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
           const glm::vec3& front    = glm::vec3(1.0f, 0.0f, 0.0f),
           const glm::vec3& up       = glm::vec3(0.0f, 1.0f, 0.0f),
           float azimuth   = 0.0f,
           float elevation = 0.0f,
           float speed     = 50.0f,
           float fov       = 45.0f,
           const float minRenderDistance = 100,
           const float maxRenderDistance = 1000000);

    /**
     * @brief      Configure camera perspective.
     *
     * @param[in]  aspectRatio  The aspect ratio
     */
    void configurePerspective(double aspectRatio);



    /**
     * @brief      Updates the camera position and orientation.
     */
    void update();

    /**
     * @brief Compute new camera position.
     * 
     * @param keyStates Array of all key states.
     * @param deltaTime Time since the last frame (in seconds).
     */
    void computeNewPosition(const std::array<bool, 1024>& keyStates, float deltaTime);

    /**
     * @brief      Compute new camera orientation.
     *
     * @param[in]  xOffset  The offset
     * @param[in]  yOffset  The y offset
     */
    void computeNewOrientation(const double xOffset, const double yOffset);

    // Setters
    void setPosition(const glm::vec3& position);
    void setSpeed(float speed);

    // Getters
    const glm::vec3& getPosition() const { return m_position; }
    const glm::vec3& getFront() const { return m_front; }
    const glm::vec3& getUp() const { return m_up; }
    const float getSpeed() const { return m_speed; }

private:

    glm::vec3 m_position; ///< Camera position (in scene unit).
    glm::vec3 m_front;    ///< Normalized direction towards which the camera is oriented (in scene unit).
    glm::vec3 m_up;       ///< Normalized direction to top of camera (in scene unit).
    glm::vec3 m_right;    ///< Normalized direction to the right of camera (in scene unit).

    float m_azimuth;   ///< Azimut angle of the camera (in °).
    float m_elevation; ///< Elevation angle of the camera (in °).

    float m_speed; ///< Camera speed (in scene unit/sec).
    float m_fov;   ///< Camera field of view (in °).

    const float m_minRenderDistance; ///< Minimal rendering distance (in scene unit).
    const float m_maxRenderDistance; ///< Maximal rendering distance (in scene unit).
};

#endif // CAMERA_H
