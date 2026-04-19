#include "application.h"

Application::Application()
:
    m_renderer()
{

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
