#include "application.h"

Application::Application(const Config& config)
:
    m_config(config),
    m_universe(config),
    m_renderer(config)
{
    // Open dataFile if dataFileName provided
    if (!m_config.dataFileName.empty()) {
        m_logFile.open(m_config.dataFileName);
        if (!m_logFile.is_open()) {
            std::cerr << "Error opening file: " << m_config.dataFileName << std::endl;
        }
    }
}

Application::~Application() {
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

void Application::start() {

    while (m_renderer.isRunning()) {
        if (m_renderer.getRunTime() * m_config.speedFactor > m_universe.m_simuationTime && m_universe.m_isRunning) {
            m_universe.makeStep();

            // Save universe current step
            if (m_logFile.is_open()) {
                m_universe.saveStep(m_logFile);
            }
        }
        m_renderer.renderFrame(m_universe);
    }
}
