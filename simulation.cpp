#include "simulation.h"
#include <iostream>

Simulation::Simulation(const std::vector<Particle>& particles, double gravite, double deltaTime, double solY, double coefficientRestitution)
    : particles(particles), gravite(gravite), deltaTime(deltaTime), solY(solY), coefficientRestitution(coefficientRestitution) {}

void Simulation::run(int steps, const std::string& filename) {
    std::ofstream file;
    if (!filename.empty()) {
        file.open(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }
    }

    for (int i = 0; i < steps; ++i) {
        double currentTime = i * deltaTime;

        for (Particle& particle : particles) {
            particle.update(deltaTime, solY, coefficientRestitution);
            particle.printState(currentTime);
            
            if (file.is_open()) {
                file << currentTime << "," << particle.getX() << "," << particle.getY() << "\n";
            }
        }

        if (allParticlesAtRest()) {
            break;
        }
    }

    if (file.is_open()) {
        file.close();
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
