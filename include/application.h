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
    */
    Application();

    /**
     * @brief      load a configuration.
     *
     * @param[in]  config  The configuration
     */
    void loadConfig(const Config& config);

    /**
     * @brief      unload the current configuration.
     */
    void unloadConfig();

    /**
     * @brief      Start the application.
     */
    void start();

private:
    std::unique_ptr<Universe> m_universe;
    Renderer m_renderer;
};

#endif
