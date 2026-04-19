#include "application.h"

Application::Application(const Config& config)
:
    m_config(config),
    m_renderer(config)
{

}

void Application::loadUniverse(const Config& config) {
    m_universe = std::make_unique<Universe>(config);
    m_renderer.setUniversePtr(m_universe.get());
}

void Application::unloadUniverse() {
    m_universe.reset();
    m_renderer.setUniversePtr(nullptr);
}

void Application::start() {

    while (m_renderer.isRunning()) {
        if (m_universe && m_renderer.getRunTime() * m_config.speedFactor > m_universe->m_simuationTime && m_universe->m_isRunning) {
            m_universe->makeStep();
        }
        m_renderer.renderFrame();
    }
}
