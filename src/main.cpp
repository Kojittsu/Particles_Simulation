#include "universe.h"
#include "SFML_functions.h"

int main() {
    // Read configuration
    Config config;
    if (!readConfig("config.json", config)) {
        return 1;
    }

    // Create universe
    Universe universe(config);

    // Add random particles
    // double maxVelocity = 1.0;
    // double minRadius = 0.1;
    // double maxRadius = 0.2;
    // for(int i=0; i< 100; i++){universe.addRndParticle(maxVelocity, minRadius, maxRadius);}
    
    // Run universe
    universe.run("data.csv");

    // Read particles movements data in file
    std::vector<std::vector<Coordinate>> particlesMovements = readParticlesMovements("data.csv");

    // Display simulation in SFML
    // int scaleFactorPixels = 100;
    std::vector<double> particlesRadius = universe.getParticlesRadius(); // Get all radius
    display_universe_SFML(particlesMovements, config.box, config.circle, particlesRadius, config.scaleFactorPixels);

    return 0;
}
