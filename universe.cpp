#include "universe.h"
#include <iostream>

Universe::Universe(const std::vector<Particle>& particles, double deltaTime)
    : particles(particles), deltaTime(deltaTime) {}

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
            particle.update(deltaTime);
            particle.printState(currentTime);
            handleBoxCollision(particle,-5.0, 5.0, 1.0, 100.0);
            
            if (file.is_open()) {
                file << currentTime << "," << particle.getX() << "," << particle.getY() << "\n";
            }
        }
    }

    if (file.is_open()) {
        file.close();
    }
}

void Universe::handleBoxCollision(Particle &particle,double xMin, double xMax, double yMin, double yMax){
    if (particle.getX() <= xMin || particle.getX() >= xMax){
        particle.setVX(-particle.getVX());
    }
    if (particle.getY() <= yMin || particle.getY() >= yMax){
        particle.setVY(-particle.getVY());
    }
}