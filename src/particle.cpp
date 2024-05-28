#include "particle.h"

// Constructor
Particle::Particle(const std::array<double, 2>& position, const std::array<double, 2>& velocity, const std::array<double, 2>& acceleration)
    : position(position), velocity(velocity), acceleration(acceleration) {}

// Getters for position
double Particle::getX() const {return position[0];}
double Particle::getY() const {return position[1];}

// Setters for position
void Particle::setX(double x) {position[0] = x;}
void Particle::setY(double y) {position[1] = y;}

// Getters for velocity
double Particle::getVX() const {return velocity[0];}
double Particle::getVY() const {return velocity[1];}

// Setters for velocity
void Particle::setVX(double vx) {velocity[0] = vx;}
void Particle::setVY(double vy) {velocity[1] = vy;}

// Update particle
void Particle::update(double deltaTime) {
    // Mise à jour de la vitesse avec l'accélération
    velocity[0] += acceleration[0] * deltaTime;
    velocity[1] += acceleration[1] * deltaTime;

    // Mise à jour de la position avec la vitesse
    position[0] += velocity[0] * deltaTime;
    position[1] += velocity[1] * deltaTime;
}

// Print particle state
void Particle::printState(double currentTime) const {
    std::cout << "Temps: " << currentTime << "s, Position: (" << position[0] << ", " << position[1] << ")\n";
}