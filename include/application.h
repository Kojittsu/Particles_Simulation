#ifndef APPLICATION_H
#define APPLICATION_H

#include <fstream>

#include "config.h"
#include "universe.h"
#include "renderer.h"

class Application {
public:
    /**
    * @brief      Initialize the application.
    *
    * @param[in]  config  The simulation configuration
    */
    Application(const Config& config);

    /**
     * @brief      Destroys the application.
     */
    ~Application();

    /**
     * @brief      Start the application.
     */
    void start();

private:
    Config m_config;
    std::ofstream m_logFile;
    Universe m_universe;
    Renderer m_renderer;
};

#endif
