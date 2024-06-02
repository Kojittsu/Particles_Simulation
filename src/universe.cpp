#include "universe.h"
#include "utils.h"
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
    int particle_number = 1;
    for (Particle& particle : particles){
        if (file.is_open()) {
            file << currentTime << "," << particle_number << "," << particle.getX() << "," << particle.getY() << "\n";
        }
        particle_number += 1;
    }
}

void Universe::addRndParticle(double maxVelocity, double minRadius, double maxRadius){
    std::array<double, 2> position = {RndNumber(box.getXMIN(), box.getXMAX()), RndNumber(box.getYMIN(), box.getYMAX())};
    std::array<double, 2> velocity = {RndNumber(-maxVelocity, maxVelocity), RndNumber(-maxVelocity, maxVelocity)};
    std::array<double, 2> acceleration = {0.0, 0.0};

    Particle particle(position, velocity, acceleration, RndNumber(minRadius, maxRadius));
    particles.push_back(particle);
}

std::vector<double> Universe::getParticlesRadius(){
    std::vector<double> particlesRadius;
    for (Particle& particle : particles){
        particlesRadius.push_back(particle.getRadius());
        std::cout << particle.getRadius() << "\n";
    }
    return particlesRadius;
}


void Universe::handleBoxCollision(Particle &particle, double coefficientRestitution){

    // Left collision
    if(particle.getX() < box.getXMIN() + particle.getRadius()){
        particle.setX(box.getXMIN() + particle.getRadius());
        particle.setVX(-particle.getVX()*coefficientRestitution);
    }
    // Right collision
    if(particle.getX() > box.getXMAX() - particle.getRadius()){
        particle.setX(box.getXMAX() - particle.getRadius());
        particle.setVX(-particle.getVX()*coefficientRestitution);
    }
    // Down collision
    if(particle.getY() < box.getYMIN() + particle.getRadius()){
        particle.setY(box.getYMIN() + particle.getRadius());
        particle.setVY(-particle.getVY()*coefficientRestitution);
    }
    // Up collision
    if(particle.getY() > box.getYMAX() - particle.getRadius()){
        particle.setY(box.getYMAX() - particle.getRadius());
        particle.setVY(-particle.getVY()*coefficientRestitution);
    }
}