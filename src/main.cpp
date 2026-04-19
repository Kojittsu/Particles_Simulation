#include "config.h"
#include "application.h"

int main(int argc, char* argv[]) {
    // Check if the configuration file name is provided
    if (argc != 2 ) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    const std::string configFile = argv[1];

    // Read configuration
    Config config;
    if (!readConfig(configFile, config)) {
        return 1;
    }

    Application application;

    // temporary, need to call that in renderer class using callbacks to allow load/unload while the application is running.
    application.loadConfig(config);
    // application.unloadUniverse();

    application.start();
    return 0;
}
