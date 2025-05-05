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

    /**
     * @brief      Initialize renderer.
     * This method setup the GLFW library for rendering the scene and the Dear
     * ImGui library for rendering the Graphical user interface.
     * 
     * @param[in]  config  The simulation configuration
     */
    Renderer(const Config& config);

    /**
     * @brief      Destroys the renderer.
     */
    ~Renderer();

    /**
     * @brief      Initializes the GLFW library.
     * This method is called by the constructor.
     */
    void initializeGLFW();

    /**
     * @brief      Define Callback for window framebuffer size.
     * This method is a callback function given to GLFW via
     * glfwSetFramebufferSizeCallback in initializeGLFW.
     * This method will be called automatically each time the window's
     * framebuffer size change.
     *
     * @param[in]  width   The width
     * @param[in]  height  The height
     */
    void framebufferSizeCallback(int width, int height);

    /**
     * @brief      Define Callback for cursor position.
     *
     * @param[in]  xpos  The cursor x coordinate
     * @param[in]  ypos  The cursor y coordinate
     */
    void cursorPosCallback(double xpos, double ypos);

    /**
     * @brief      Define Callback for Keyboard inputs.
     *
     * @param[in]  key       The key
     * @param[in]  scancode  The scancode
     * @param[in]  action    The action
     * @param[in]  mods      The mods
     */
    void keyboardCallback(int key, int scancode, int action, int mods);

    /**
     * @brief      Initializes the Dear ImGui library.
     * This method is called by the constructor.
     */
    void initializeImGui();

    /**
     * @brief      Renders the given universe.
     *
     * @param[in]  universe  The universe
     */
    void render(const Universe& universe);

    /**
     * @brief      Draws the m_boxes boxes.
     */
    void drawBoxes();

    /**
     * @brief      Call glfwSwapBuffers(m_window).
     */
    void swapBuffers();

    /**
     * @brief      Render Dear ImGui.
     *
     * @param      universe  The universe
     */
    void renderImGui(Universe& universe);

    /**
     * @brief      Update the camera position.
     * This method will take into account keyboard inputs for camera movement
     * when spectator mode is on.
     */
    void updateCamera();
    
    /**
     * @brief      Toggle spectator mode.
     * The spectator mode will take into account keyboard inputs for camera 
     * movement and enable/disable the cursor.
     */
    void toggleSpectatorMode();
    
    /**
     * @brief      Clears the renderer.
     */
    void clear();

    /**
     * @brief      Determines if the renderer is running.
     *
     * @return     True if running, False otherwise.
     */
    bool isRunning();

private:
    GLFWwindow* m_window;               ///< GLFW window pointer.
    const Config& m_config;             ///< Reference to simulation configuration.
    std::vector<Box> m_boxes;           ///< Vector of Box.
    GLUquadric* m_quadric;              ///< GLU Utility for rendering quadratic shapes.

    const float m_minRenderDistance = 0.1;        ///< Minimal rendering distance (in scene unit).
    const float m_maxRenderDistance = 1000;    ///< Maximal rendering distance (in scene unit).

    float m_azimuth = 0.0f;       ///< Azimut angle of the camera (in °).
    float m_elevation = 0.0f;     ///< Elevation angle of the camera (in °).

    float m_lastX = 400.0f;       ///< Last cursor X position. unit ADU
    float m_lastY = 300.0f;       ///< Last cursor Y position.

    glm::vec3 m_cameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);    ///< Camera position (in scene unit).
    glm::vec3 m_cameraFront    = glm::vec3(1.0f, 0.0f, 0.0f);    ///< Normalized direction towards which the camera is oriented (in scene unit).
    glm::vec3 m_cameraUp       = glm::vec3(0.0f, 1.0f, 0.0f);    ///< Normalized direction to top of camera (in scene unit).
    glm::vec3 m_cameraRight;                                     ///< Normalized direction to the right of camera (in scene unit).
    float m_cameraSpeed = 50.0f;                                 ///< Camera speed (in scene unit/sec).

    double m_lastFrameTime = 0.0;   ///< GLFW time of the last frame (in seconds).

    bool m_keyStates[1024] = {false}; ///< Key states.

    bool m_isSpectatorMode = false; ///< Determines if spectator is enable.

};

#endif // RENDERER_H
