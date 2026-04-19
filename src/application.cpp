#include "application.h"

Application::Application(const Config& config)
:
    m_renderer(config.rendererConfig)
{

}

void Application::loadUniverse(const UniverseConfig& universeConfig) {
    m_universe = std::make_unique<Universe>(universeConfig);
    m_renderer.setUniversePtr(m_universe.get());
}

void Application::unloadUniverse() {
    m_universe.reset();
    m_renderer.setUniversePtr(nullptr);
}

void Application::start() {

    while (m_renderer.isRunning()) {
        if (m_universe && m_universe->m_isRunning && m_renderer.universeShouldMakeStep()) {
            m_universe->makeStep();
        }
        m_renderer.renderFrame();
    }
}
