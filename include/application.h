#ifndef APPLICATION_H
#define APPLICATION_H

#include "config.h"
#include "universe.h"
#include "renderer.h"
#include "tinyfiledialogs.h"

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
    std::unique_ptr<Universe> universe_;
    Renderer renderer_;

    #define CONFIG_EXAMPLES_DIR_ "@CONFIG_EXAMPLES_DIR@"
};

#endif
