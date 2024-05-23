#include <iostream>
#include <vector>
#include <cmath>
#include "particle.h"

int main() {

    // Parameters
    const double gravite = -9.81;  // Gravity Acceleration (m/s^2)
    const double deltaTime = 0.01; // Time step of simulation (s)
    const double solY = 0.0;       // Floor Y coordinate
    const double coefficientRestitution = 0.1; // Energy particle restitution coefficient

    // Particles initialisation
    std::vector<Particle> particles;
    particles.emplace_back(0.0, 10.0, 0.0, 0.0, 0.0, gravite); // Particule à 10m de hauteur avec vitesse initiale nulle

    // Simulation
    for (int i = 0; i < 1000; ++i) {
        double currentTime = i * deltaTime;
        
        for (Particle& particle : particles) {
            particle.update(deltaTime, solY, coefficientRestitution);
            particle.printState(currentTime);
        }

        // Break loop if all particles at rest
        bool allAtRest = true;
        for (const Particle& particle : particles) {
            if (!particle.isAtRest(solY)) {
                allAtRest = false;
                break;
            }
        }
        if (allAtRest) {
            break;
        }
    }

    return 0;
}