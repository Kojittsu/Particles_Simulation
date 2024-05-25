#include "universe.h"
#include <iostream>

Universe::Universe(const std::vector<Particle>& particles, double gravite, double deltaTime, double solY, double coefficientRestitution)
    : particles(particles), gravite(gravite), deltaTime(deltaTime), solY(solY), coefficientRestitution(coefficientRestitution) {}

void Universe::run(int steps, const std::string& filename) {
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
    }

    if (file.is_open()) {
        file.close();
    }
}