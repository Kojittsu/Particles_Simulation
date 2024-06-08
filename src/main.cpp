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
    double maxMass            = 100;




    // // Set earth
    // std::array<double, 2> earthPosition = {0.0, 0.0};
    // std::array<double, 2> earthVelocity = {0.0, 0.0};
    // double earthMass = 5.972e24;
    // double earthRadius = 6378100.0;
    // Particle earth(earthPosition, earthVelocity, earthRadius, earthMass);

    // // Set moon
    // std::array<double, 2> moonPosition = {384400000.0, 0.0};
    // std::array<double, 2> moonVelocity = {0.0, 1022.0};
    // double moonMass = 7.348e22;
    // double moonRadius = 1738100.0;
    // Particle moon(moonPosition, moonVelocity, moonRadius, moonMass);

    // universe.addParticle(earth);
    // universe.addParticle(moon);





    // Add random particles
    for(int i=0; i< randomParticleNumbers; i++){
        universe.addRndParticle(maxVelocityX, maxVelocityY, minRadius, maxRadius, maxMass);
    }
    
    // Run universe
    universe.run("data.csv");

    // Read particles movements data in file
    std::vector<std::vector<Coordinate>> particleMovements = readParticleMovements("data.csv");

    // Display simulation in SFML
    std::vector<double> particlesRadius = universe.getParticlesRadius(); // Get all radius
    RenderParticleMovements(particleMovements, config.box, config.circle, particlesRadius, config.scaleFactorPixels);

    return 0;
}
