#ifndef RENDERER_H
#define RENDERER_H

#include "universe.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>  // For gluPerspective
#include <glm/glm.hpp> // For mathematics Opengl
#include <vector>
#include <array>

class Renderer {
public:
    Renderer(GLFWwindow* window, const Config& config);
    ~Renderer();

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void processKeyboardInput();
    void updateCameraView();
    void render(const Universe& universe);
    void clear();
    void drawBox(double xOrigin, double yOrigin, double zOrigin, double length, double height, double depth);

private:
    GLFWwindow* m_window;
    const Config& m_config;
    GLUquadric* m_quadric;

    // Render distance parameters
    const float m_minRenderDistance = 0.1;
    const float m_maxRenderDistance = 1000;

    // Variables for angles of rotation
    float m_azimuth = 0.0f;
    float m_elevation = 0.0f;

    // Initial cursor position (center of window)
    float m_lastX = 400.0f;
    float m_lastY = 300.0f;
    bool m_firstMouse = true;

    glm::vec3 m_cameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);
    float m_cameraSpeed = 50.0f;
    glm::vec3 m_cameraFront = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_cameraRight;

    double m_lastFrameTime = 0.0;
};

#endif // RENDERER_H
