#include <iostream>

#include "universe.h"
#include "renderer.h"

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

    // Create renderer
    Renderer renderer(config);

    // Main loop
    while (renderer.isRunning()) {
        
        if (renderer.getRunTime() * config.speedFactor > universe.m_simuationTime && universe.m_isRunning) {
            universe.makeStep();

            // Save universe current step
            if (file.is_open()) {
                universe.saveStep(file);
            }
        }

        renderer.clear();
        renderer.render(universe);
        renderer.drawBoxes();
        renderer.renderImGui(universe);

        renderer.swapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();

    if (file.is_open()) {
        file.close();
    }

    return 0;
}
