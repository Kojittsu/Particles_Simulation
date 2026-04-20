#include "application.h"

Application::Application()
:
    m_renderer()
{
    // Set m_renderer callbacks
    m_renderer.setLoadConfigCallback([this](const std::string& configFilePath) {
        // Read configuration
        Config config;
        if (!readConfig(configFilePath, config)) {
            return;
        }
        loadConfig(config);
    });
    m_renderer.setUnloadConfigCallback([this]() {
        unloadConfig();
    });
}

void Application::loadConfig(const Config& config) {
    m_universe = std::make_unique<Universe>(config.universeConfig);
    m_renderer.setUniversePtr(m_universe.get());
    m_renderer.updateConfig(config.rendererConfig);
}

void Application::unloadConfig() {
    m_universe.reset();
    m_renderer.resetCurrentUniverse();
}

void Application::start() {

    while (m_renderer.isRunning()) {
        if (m_universe && m_universe->m_isRunning && m_renderer.universeShouldMakeStep()) {
            m_universe->makeStep();
        }
        m_renderer.renderFrame();
    }
}
