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

    // Parameters
    // Random particle parameters
    int randomParticleNumbers = 0;
    double maxVelocityX       = 0.0;
    double maxVelocityY       = 0.0;
    double minRadius          = 0.1;
    double maxRadius          = 0.2;
    // Gravity parameters
    double AccelerationX      = 0.0;
    double AccelerationY      = -9.81;

    // Add random particles
    for(int i=0; i< randomParticleNumbers; i++){
        universe.addRndParticle(maxVelocityX, maxVelocityY, minRadius, maxRadius);
    }

    // Apply gravity to all particles
    universe.applyGravityToParticles(AccelerationX, AccelerationY);
    
    // Run universe
    universe.run("data.csv");

    // Read particles movements data in file
    std::vector<std::vector<Coordinate>> particleMovements = readParticleMovements("data.csv");

    // Display simulation in SFML
    std::vector<double> particlesRadius = universe.getParticlesRadius(); // Get all radius
    RenderParticleMovements(particleMovements, config.box, config.circle, particlesRadius, config.scaleFactorPixels);

    return 0;
}
