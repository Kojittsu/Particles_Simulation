#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include "array.h"

class Camera {
public:
    /**
    * @brief      Initialize camera.
    */
    Camera() = default;

    /**
     * @brief      Configure camera perspective.
     *
     * @param[in]  aspectRatio  The aspect ratio
     */
    void configurePerspective(const double aspectRatio);

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
    void computeNewPosition(const std::array<bool, 1024>& keyStates, const float deltaTime);

    /**
     * @brief      Compute new camera orientation.
     *
     * @param[in]  xOffset  The offset
     * @param[in]  yOffset  The y offset
     */
    void computeNewOrientation(const double xOffset, const double yOffset);

    /**
     * @brief      Reset camera.
     */
    void reset();

    // Setters
    void setPosition(const glm::vec3& position);
    void setSpeed(const float& speed);

    // Getters
    glm::vec3 getPosition() const {return position_;}
    glm::vec3 getFront() const {return front_;}
    glm::vec3 getUp() const {return up_;}
    float getSpeed() const {return speed_;}

private:
    glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f);          ///< Camera position (in scene unit).
    glm::vec3 front_    = glm::vec3(1.0f, 0.0f, 0.0f);          ///< Normalized direction towards which the camera is oriented (in scene unit).
    glm::vec3 up_       = glm::vec3(0.0f, 1.0f, 0.0f);          ///< Normalized direction to top of camera (in scene unit).
    glm::vec3 right_ = glm::normalize(glm::cross(front_, up_)); ///< Normalized direction to the right of camera (in scene unit).

    float azimuth_ = 0.0f;   ///< Azimut angle of the camera (in °).
    float elevation_ = 0.0f; ///< Elevation angle of the camera (in °).
    float speed_ = 50.0f; ///< Camera speed (in scene unit/sec).
    static constexpr float sensitivity_ = 0.1f; ///< Camera sensitivity.
    static constexpr float fov_ = 45.0f;   ///< Camera field of view (in °).
    static constexpr float minRenderDistance_ = 1.0;     ///< Minimal rendering distance (in scene unit).
    static constexpr float maxRenderDistance_ = 10000.0; ///< Maximal rendering distance (in scene unit).
};

#endif // CAMERA_H
