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

    if(particle.getX() <= box.getXMIN()){
        std::cout << "Collision (left): changing X-axis velocity sign"  << "\n";
        particle.setX(box.getXMIN());
        particle.setVX(-particle.getVX()*0.9);
    }
    if(particle.getX() >= box.getXMAX()){
        std::cout << "Collision (right): changing X-axis velocity sign"  << "\n";
        particle.setX(box.getXMAX());
        particle.setVX(-particle.getVX()*0.9);
    }
    if(particle.getY() <= box.getYMIN()){
        std::cout << "Collision (down): changing Y-axis velocity sign"  << "\n";
        particle.setY(box.getYMIN());
        particle.setVY(-particle.getVY()*0.9);
    }
    if(particle.getY() >= box.getYMAX()){
        std::cout << "Collision (up): changing Y-axis velocity sign"  << "\n";
        particle.setY(box.getYMAX());
        particle.setVY(-particle.getVY()*0.9);
    }
}