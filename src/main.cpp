#include "universe.h"
#include "renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

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

    // Main loop
    while (!glfwWindowShouldClose(window)) {

        if (glfwGetTime() * config.speedFactor > universe.m_runTime) {
            universe.makeStep();

            // Save universe current step
            if (file.is_open()) {
                universe.saveStep(file, stepNumberSaved);
                stepNumberSaved++;
            }
        }

        renderer.clear();
        renderer.updateCamera();
        renderer.render(universe);
        renderer.drawBox();
        renderer.renderImGui(universe);

        // Swap buffers
        glfwSwapBuffers(window);

        // Handle events
        glfwPollEvents();
    }

    glfwTerminate();

    if (file.is_open()) {
        file.close();
    }

    return 0;
}
