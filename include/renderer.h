#ifndef RENDERER_H
#define RENDERER_H

#include "universe.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>  // For gluPerspective
#include <vector>
#include <array>

class Renderer {
public:
    Renderer(GLFWwindow* window, const Config& config);
    ~Renderer();

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void updateCameraView();
    void render(const Universe& universe);
    void clear();
    void drawBox(double xOrigin, double yOrigin, double zOrigin, double length, double height, double depth);

    // Variables for angles of rotation
    float m_azimuth = 0.0f;
    float m_elevation = 0.0f;
    float m_radius = 50.0f;

    // Initial cursor position (center of window)
    float m_lastX = 400.0f;
    float m_lastY = 300.0f;
    bool m_firstMouse = true;

    // Render distance parameters
    const float m_minRenderDistance = 0.1;
    const float m_maxRenderDistance = 1000;

private:
    GLFWwindow* m_window;
    const Config& m_config;
    GLUquadric* m_quadric;
};

#endif // RENDERER_H
