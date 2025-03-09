#include "universe.h"
#include "renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int main(int argc, char* argv[]) {
    // Check if the configuration file name is provided
    if (argc != 2 ) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    const std::string configFile = argv[1];

    // Read configuration
    Config config;
    if (!readConfig(configFile, config)) {
        return 1;
    }

    // Create universe
    Universe universe(config);

    // Open dataFile if dataFileName provided
    std::ofstream file;
    if (!config.dataFileName.empty()) {
        file.open(config.dataFileName);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << config.dataFileName << std::endl;
            return 1;
        }
    }
    int stepNumberSaved = 0;

    // GLFW init
    if (!glfwInit()) {
        return -1;
    }

    // Create window
    GLFWwindow* window = glfwCreateWindow(900, 600, "Particle System", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Create renderer
    Renderer renderer(window, config);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    glfwMakeContextCurrent(window);

    // ImGui/Glfw bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    float sliderTestValue = 0.0f;

    // Main loop
    while (!glfwWindowShouldClose(window)) {

        double currentTime = glfwGetTime();

        if (currentTime * config.speedFactor > universe.m_runTime) {

            renderer.clear();

            renderer.processInput();

            universe.makeStep();
            renderer.updateCameraView();
            renderer.render(universe);
            renderer.drawBox();


            // Start new ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::Begin("Contrôles", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::Text("sliderTestValue : %f", sliderTestValue);
            ImGui::SliderFloat("sliderTest", &sliderTestValue, -5.0f, 5.0f);
            ImGui::End();

            // Render ImGui
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap buffers
            glfwSwapBuffers(window);

            // Handle events
            glfwPollEvents();

            // Save universe current step
            if (file.is_open()) {
                universe.saveStep(file, stepNumberSaved);
                stepNumberSaved++;
            }
        }
    }

    glfwTerminate();

    if (file.is_open()) {
        file.close();
    }

    return 0;
}
