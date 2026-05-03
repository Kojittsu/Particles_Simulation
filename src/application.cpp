#include "application.h"

Application::Application()
:
    renderer_()
{
    // Set renderer callbacks
    renderer_.setLoadConfigCallback([this](const std::string& configFilePath) {
        // Read configuration
        Config config;
        if (readConfig(configFilePath, config)) {
            loadConfig(config);
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
        if (universe_ && universe_->m_isRunning && renderer_.universeShouldMakeStep()) {
            universe_->makeStep();
        }
        renderer_.renderFrame();
    }
}
