#include "application.h"

Application::Application()
:
    renderer_()
{
    // Set renderer callbacks
    renderer_.setLoadConfigCallback([this]() {

        const char* configFilePath = tinyfd_openFileDialog("Select a file", CONFIG_EXAMPLES_DIR_, 0, NULL, NULL, 0);

        // Check if file selected
        if (configFilePath) {
            const std::string configFilePathStr(configFilePath);
            // Read configuration
            Config config;
            if (readConfig(configFilePathStr, config)) {
                loadConfig(config);
            }
        }
    });

    renderer_.setUnloadConfigCallback([this]() {
        unloadConfig();
    });
}

void Application::loadConfig(const Config& config) {
    universe_ = std::make_unique<Universe>(config.universeConfig);
    renderer_.setUniversePtr(universe_.get());
    renderer_.updateConfig(config.rendererConfig);
}

void Application::unloadConfig() {
    universe_.reset();
    renderer_.resetCurrentUniverse();
}

void Application::start() {

    while (renderer_.isRunning()) {
        if (universe_ && universe_->isRunning_ && renderer_.universeShouldMakeStep()) {
            universe_->makeStep();
        }
        renderer_.renderFrame();
    }
}
