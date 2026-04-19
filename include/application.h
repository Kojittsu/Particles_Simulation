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
     * @brief      load the universe provide by config.
     *
     * @param[in]  config  The simulation configuration
     */
    void loadUniverse(const Config& config);

    /**
     * @brief      unload the current universe.
     */
    void unloadUniverse();

    /**
     * @brief      Start the application.
     */
    void start();

private:
    Config m_config;
    std::ofstream m_logFile;
    std::unique_ptr<Universe> m_universe;
    Renderer m_renderer;
};

#endif
