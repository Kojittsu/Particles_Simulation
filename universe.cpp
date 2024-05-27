#include "universe.h"
#include <iostream>

Universe::Universe(const std::vector<Particle>& particles, const Box &box, const double coefficientRestitution, double deltaTime)
    : particles(particles), box(box), coefficientRestitution(coefficientRestitution), deltaTime(deltaTime) {}

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
        make_step(i);
        save_step(file, i);
    }

    if (file.is_open()) {
        file.close();
    }
}

void Universe::make_step(int i){
    for (Particle& particle : particles) {
        particle.update(deltaTime);
        handleBoxCollision(particle, coefficientRestitution);
    }
}


void Universe::save_step(std::ofstream &file, int step_number){
    double currentTime = step_number * deltaTime;
    for (Particle& particle : particles){
        if (file.is_open()) {
            file << currentTime << "," << particle.getX() << "," << particle.getY() << "\n";
        }
    }
}


void Universe::handleBoxCollision(Particle &particle, double coefficientRestitution){

    if(particle.getX() <= box.getXMIN()){
        std::cout << "Collision (left): changing X-axis velocity sign"  << "\n";
        particle.setX(box.getXMIN());
        particle.setVX(-particle.getVX()*coefficientRestitution);
    }
    if(particle.getX() >= box.getXMAX()){
        std::cout << "Collision (right): changing X-axis velocity sign"  << "\n";
        particle.setX(box.getXMAX());
        particle.setVX(-particle.getVX()*coefficientRestitution);
    }
    if(particle.getY() <= box.getYMIN()){
        std::cout << "Collision (down): changing Y-axis velocity sign"  << "\n";
        particle.setY(box.getYMIN());
        particle.setVY(-particle.getVY()*coefficientRestitution);
    }
    if(particle.getY() >= box.getYMAX()){
        std::cout << "Collision (up): changing Y-axis velocity sign"  << "\n";
        particle.setY(box.getYMAX());
        particle.setVY(-particle.getVY()*coefficientRestitution);
    }
}