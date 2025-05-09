#ifndef RENDERER_H
#define RENDERER_H

#include "universe.h"
#include "camera.h"
#include "array.h"

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
     * @brief      Toggle spectator mode.
     * The spectator mode will take into account keyboard and mouse inputs for
     * camera movement and show/hide the cursor.
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

    // Getters
    const double& getRunTime() const { return m_runTime; }


private:
    GLFWwindow* m_window;               ///< GLFW window pointer.
    const Config& m_config;             ///< Reference to simulation configuration.
    std::vector<Box> m_boxes;           ///< Vector of Box.
    GLUquadric* m_quadric;              ///< GLU Utility for rendering quadratic shapes.
    Camera m_camera;

    float m_lastX = 400.0f;       ///< Last cursor X position (in pixels).
    float m_lastY = 300.0f;       ///< Last cursor Y position (in pixels).

    double m_lastFrameTime = 0.0;   ///< GLFW time of the last frame (in seconds).
    double m_simulationTimePaused = 0.0;
    double m_runTime = 0.0;

    std::array<bool, 1024> m_keyStates{ {false} }; ///< States of the keys.

    bool m_isSpectatorMode = false; ///< Determines if spectator is enable.

    double m_scaleFactor;
};

#endif // RENDERER_H
