#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <glm/glm.hpp>

#include "universe.h"
#include "camera.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

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
     * @brief      Initializes the imPlot library.
     * This method is called by the constructor.
     */
    void initializeImPlot();

    /**
     * @brief      Renders the given universe.
     *
     * @param[in]  universe  The universe
     */
    void render(Universe& universe);

    /**
     * @brief      Render the trail of the given particle.
     *
     * @param      particle  The particle
     */
    void renderParticleTrail(const Particle& particle);

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
     * @brief      Render control ImGui menu.
     *
     * @param      universe      The universe
     * @param[in]  window_flags  The window flags
     */
    void ImGuiControlsMenu(Universe& universe, ImGuiWindowFlags window_flags);

    /**
     * @brief      Render particles viewer ImGui menu.
     *
     * @param      particles  The particles
     * @param      window_flags  The window flags
     */
    void ImGuiParticleViewerMenu(std::vector<Particle>& particles, ImGuiWindowFlags window_flags);

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

    /**
     * @brief      Return the run time.
     *
     * @return     The run time
     */
    const double& getRunTime() const { return m_runTime; }


private:
    GLFWwindow* m_window;               ///< GLFW window pointer.
    const Config& m_config;             ///< Reference to simulation configuration.
    std::vector<Box> m_boxes;           ///< Vector of Box.
    GLUquadric* m_quadric;              ///< GLU Utility for rendering quadratic shapes.
    Camera m_camera;

    float m_lastX = 0.0f;       ///< Last cursor X position (in pixels).
    float m_lastY = 0.0f;       ///< Last cursor Y position (in pixels).

    double m_lastFrameTime = 0.0;   ///< GLFW time of the last frame (in seconds).
    double m_simulationTimePaused = 0.0;
    double m_runTime = 0.0;

    std::array<bool, 1024> m_keyStates{ {false} }; ///< States of the keys.

    bool m_isSpectatorMode = false; ///< Determines if spectator is enable.

    double m_scaleFactor; ///< Scale factor applied for rendering.

    std::vector<float> m_lastFrameratesBuffer; ///< vector of last framerates values
    std::vector<float> m_lastFrameratesIndexes; ///< vector of last framerates indexes
};

#endif // RENDERER_H
