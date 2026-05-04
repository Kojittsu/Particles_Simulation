#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glu.h>

#include "universe.h"
#include "camera.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "tinyfiledialogs.h"

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
     * @brief      Set the callback for loading config.
     * @param[in]  cb  The callback function
     */
    void setLoadConfigCallback(std::function<void(const std::string&)> cb);

    /**
     * @brief      Set the callback for unloading config.
     * @param[in]  cb  The callback function
     */
    void setUnloadConfigCallback(std::function<void()> cb);

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
     * @brief      Render a grid at y = 0.
     */
    void renderGrid();

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
    const double& getRuntime() const { return currentUniverseRuntime_; }


private:
    GLFWwindow* window_ = nullptr;     ///< GLFW window pointer.
    Universe* universePtr_ = nullptr;  ///< Universe pointer.
    GLUquadric* quadric_;              ///< GLU Utility for rendering quadratic shapes.
    Camera camera_;

    std::function<void(const std::string&)> loadConfigCallback_;  ///< Callback for loading config
    std::function<void()> unloadConfigCallback_;                  ///< Callback for unloading config

    // ImGui flags
    static constexpr ImGuiWindowFlags windowFlags_ = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground;
    static constexpr ImGuiDockNodeFlags dockSpaceFlags_ = ImGuiDockNodeFlags_PassthruCentralNode;

    float lastX_ = 0.0f;       ///< Last cursor X position (in pixels).
    float lastY_ = 0.0f;       ///< Last cursor Y position (in pixels).

    double lastFrameTime_ = 0.0;   ///< GLFW time of the last frame (in seconds).

    // current universe variables
    double currentUniverseTimePaused_ = 0.0;
    double currentUniverseRuntime_ = 0.0;
    double speedFactor_ = 1.0; ///< Speed factor applied for rendering universe at different speeds.
    double scaleFactor_ = 1.0; ///< Scale factor applied for rendering : 1 SU = 1 meter * scaleFactor. (SU mean System Unit)

    std::array<bool, 1024> keyStates_{ {false} }; ///< States of the keys.

    bool isSpectatorMode_ = false; ///< Determines if spectator is enable.
    bool renderParticleTrails_ = false; ///< Determines if renderer should render particle trails.

    std::vector<float> lastFrameratesBuffer_; ///< vector of last framerates values
    std::vector<float> lastFrameratesIndexes_; ///< vector of last framerates indexes

    // grid members
    bool renderGrid_ = false; ///< Determines if renderer should render grid.
    static constexpr float gridLength_ = 10000; ///< grid length (in SU)
    static constexpr float gridOpacity_ = 0.3; ///< grid opacity (in [0,1])
    static constexpr float gridStep_ = 100.0; ///< grid step length (in SU)
};

#endif // RENDERER_H
