#include "particle.h"

// Constructor
Particle::Particle(double x, double y, double vx, double vy, double ax, double ay)
    : position({x, y}), velocity({vx, vy}), acceleration({ax, ay}) {}

// Getter for x
double Particle::getX() const {
    return position[0];
}

// Getter for y
double Particle::getY() const {
    return position[1];
}

// Update particle
void Particle::update(double deltaTime, double solY, double coefficientRestitution) {
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