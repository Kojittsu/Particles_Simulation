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
     */
    Renderer();

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
     * @brief      Set the universe pointer.
     * @param[in]  universePtr  The universe pointer
     */
    void setUniversePtr(Universe* universePtr);

    /**
     * @brief      Reset the current universe.
     * set to nullptr the universe pointer and reset universe variables.
     */
    void resetCurrentUniverse();

    /**
     * @brief      update the renderer config.
     * @param[in]  rendererConfig  The renderer config
     */
    void updateConfig(const RendererConfig& rendererConfig);

    /**
     * @brief      Renders a frame.
     */
    void renderFrame();

    /**
     * @brief      Renders the scene.
     */
    void renderScene();

    /**
     * @brief      Render the the given particle.
     *
     * @param      particle  The particle
     */
    void renderParticle(const Particle& particle);

    /**
     * @brief      Render the trail of the given particle.
     *
     * @param      particle  The particle
     */
    void renderParticleTrail(const Particle& particle);

    /**
     * @brief      Render the current universe boxes.
     */
    void renderBoxes();

    /**
     * @brief      Render Dear ImGui.
     */
    void renderImGui();

    /**
     * @brief      Render control ImGui menu.
     */
    void ImGuiControlsMenu();

    /**
     * @brief      Render information ImGui menu.
     */
    void ImGuiInformationMenu();

    /**
     * @brief      Render particles viewer ImGui menu.
     */
    void ImGuiParticleViewerMenu();

    /**
     * @brief      Render particles editor ImGui menu.
     */
    void ImGuiParticleEditorMenu();

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
     * @brief      Determines if the current universe should make a step.
     *
     * @return     True if the current universe should make a step, False otherwise.
     */
    bool universeShouldMakeStep();

    /**
     * @brief      Return the current universe runtime.
     *
     * @return     The run time
     */
    const double& getRuntime() const { return m_currentUniverseRuntime; }


private:
    GLFWwindow* m_window = nullptr;     ///< GLFW window pointer.
    Universe* m_universePtr = nullptr;  ///< Universe pointer.
    GLUquadric* m_quadric;              ///< GLU Utility for rendering quadratic shapes.
    Camera m_camera;

    // ImGui flags
    ImGuiWindowFlags m_windowFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground;
    ImGuiDockNodeFlags m_dockSpaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

    float m_lastX = 0.0f;       ///< Last cursor X position (in pixels).
    float m_lastY = 0.0f;       ///< Last cursor Y position (in pixels).

    double m_lastFrameTime = 0.0;   ///< GLFW time of the last frame (in seconds).

    // current universe variables
    double m_currentUniverseTimePaused = 0.0;
    double m_currentUniverseRuntime = 0.0;
    double m_speedFactor = 1.0; ///< Speed factor applied for rendering universe at different speeds.
    double m_scaleFactor = 1.0; ///< Scale factor applied for rendering.

    std::array<bool, 1024> m_keyStates{ {false} }; ///< States of the keys.

    bool m_isSpectatorMode = false; ///< Determines if spectator is enable.

    std::vector<float> m_lastFrameratesBuffer; ///< vector of last framerates values
    std::vector<float> m_lastFrameratesIndexes; ///< vector of last framerates indexes
};

#endif // RENDERER_H
