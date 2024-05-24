#include <iostream>
#include <vector>
#include "particle.h"
#include "universe.h"

int main() {
    // Parameters
    const double gravite = -9.81;  // Gravity Acceleration (m/s^2)
    const double deltaTime = 0.01; // Time step of simulation (s)
    const double solY = 0.0;       // Floor Y coordinate
    const double coefficientRestitution = 0.1; // Energy particle restitution coefficient

    // Particles initialization
    std::vector<Particle> particles;
    particles.emplace_back(0.0, 10.0, 0.0, 0.0, 0.0, gravite); // Particle at 10m height with zero initial velocity

    // Create and run universe
    Universe universe(particles, gravite, deltaTime, solY, coefficientRestitution);
    universe.run(1000, "simulation_output.csv");

    return 0;
}
