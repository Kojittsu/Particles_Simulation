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
    Renderer(const Config& config);
    ~Renderer();

    void initializeGLFW();
    void initializeImGui();
    void framebufferSizeCallback(int width, int height);
    void cursorPosCallback(double xpos, double ypos);
    void keyboardCallback(int key, int scancode, int action, int mods);

    void updateCamera();

    void render(const Universe& universe);
    void drawBoxes();
    void toggleSpectatorMode();
    void renderImGui(Universe& universe); 
    void clear();

    GLFWwindow* m_window;

private:
    const Config& m_config;
    std::vector<Box> m_boxes;
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
    float m_cameraSpeed = 50.0f; // In m/s
    glm::vec3 m_cameraFront = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_cameraRight;

    double m_lastFrameTime = 0.0;

    bool m_keyStates[1024] = {false};

    bool m_isSpectatorMode = false;
};

#endif // RENDERER_H
