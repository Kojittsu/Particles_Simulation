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

    Box box_1(0.0, 10.0, 0.0, 10.0);

    for (int i = 0; i < steps; ++i) {
        double currentTime = i * deltaTime;

        for (Particle& particle : particles) {
            particle.update(deltaTime);
            particle.printState(currentTime);
            handleBoxCollision(particle, box_1);
            
            if (file.is_open()) {
                file << currentTime << "," << particle.getX() << "," << particle.getY() << "\n";
            }
        }
    }

    if (file.is_open()) {
        file.close();
    }
}

void Universe::handleBoxCollision(Particle &particle,const Box &box){
    if (particle.getX() <= box.getXMIN() || particle.getX() >= box.getXMAX()){
        particle.setVX(-particle.getVX());
    }
    if (particle.getY() <= box.getYMIN() || particle.getY() >= box.getYMAX()){
        particle.setVY(-particle.getVY());
    }
}