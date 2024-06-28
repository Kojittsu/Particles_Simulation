#include "universe.h"

int main(int argc, char* argv[]) {
    
    // Check if the configuration file name is provided
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << " <data_file> " << std::endl;
        return 1;
    }

    const std::string configFile = argv[1];
    const std::string dataFileName = argv[2];

    // Read configuration
    Config config;
    if (!readConfig(configFile, config)) {
        return 1;
    }

    // Create universe
    Universe universe(config);

    // Add random particles
    for(int i=0; i< config.rndParticle_numbers; i++){
        universe.addRndParticle(config.rndParticle_maxVelocityX, config.rndParticle_maxVelocityY, config.rndParticle_minRadius, config.rndParticle_maxRadius, config.rndParticle_minMass, config.rndParticle_maxMass);
    }

    // Run universe
    universe.runAndRender();

    return 0;
}
