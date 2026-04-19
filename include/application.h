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
     * @brief      load the universe provide by config.
     *
     * @param[in]  universeConfig  The universe configuration
     */
    void loadUniverse(const UniverseConfig& universeConfig);

    /**
     * @brief      unload the current universe.
     */
    void unloadUniverse();

    /**
     * @brief      Start the application.
     */
    void start();

private:
    std::unique_ptr<Universe> m_universe;
    Renderer m_renderer;
};

#endif
