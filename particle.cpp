#include "particle.h"

// Constructor
Particle::Particle(double x, double y, double vx, double vy, double ax, double ay)
    : x(x), y(y), vx(vx), vy(vy), ax(ax), ay(ay) {}

// Getter for x
double Particle::getX() const {
    return x;
}

// Getter for y
double Particle::getY() const {
    return y;
}

// Update particle
void Particle::update(double deltaTime, double solY, double coefficientRestitution) {
    // Mise à jour de la vitesse avec l'accélération
    vx += ax * deltaTime;
    vy += ay * deltaTime;

    // Mise à jour de la position avec la vitesse
    x += vx * deltaTime;
    y += vy * deltaTime;
}

// Print particle state
void Particle::printState(double currentTime) const {
    std::cout << "Temps: " << currentTime << "s, Position: (" << x << ", " << y << ")\n";
}