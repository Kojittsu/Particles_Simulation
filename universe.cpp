#include "universe.h"
#include <iostream>

Universe::Universe(const std::vector<Particle>& particles, const Box &box, double deltaTime)
    : particles(particles), box(box), deltaTime(deltaTime) {}

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
            handleBoxCollision(particle);
            
            if (file.is_open()) {
                file << currentTime << "," << particle.getX() << "," << particle.getY() << "\n";
            }
        }
    }

    if (file.is_open()) {
        file.close();
    }
}

void Universe::handleBoxCollision(Particle &particle){
    if (particle.getX() <= box.getXMIN() || particle.getX() >= box.getXMAX()){
        particle.setVX(-particle.getVX());
    }
    if (particle.getY() <= box.getYMIN() || particle.getY() >= box.getYMAX()){
        particle.setVY(-particle.getVY());
    }
}