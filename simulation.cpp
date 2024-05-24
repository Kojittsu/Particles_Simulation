#include "simulation.h"
#include <iostream>

Simulation::Simulation(const std::vector<Particle>& particles, double gravite, double deltaTime, double solY, double coefficientRestitution)
    : particles(particles), gravite(gravite), deltaTime(deltaTime), solY(solY), coefficientRestitution(coefficientRestitution) {}

void Simulation::run(int steps) {
    for (int i = 0; i < steps; ++i) {
        double currentTime = i * deltaTime;

        for (Particle& particle : particles) {
            particle.update(deltaTime, solY, coefficientRestitution);
            particle.printState(currentTime);
        }

        if (allParticlesAtRest()) {
            break;
        }
    }
}

bool Simulation::allParticlesAtRest() const {
    for (const Particle& particle : particles) {
        if (!particle.isAtRest(solY)) {
            return false;
        }
    }
    return true;
}
