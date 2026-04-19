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
     * @brief      load the universe provide by config.
     *
     * @param[in]  config  The configuration
     */
    void loadConfig(const Config& config);

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
