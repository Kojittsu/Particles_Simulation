#include "particle.h"

// Constructor
Particle::Particle(double x, double y, double vx, double vy, double ax, double ay)
    : x(x), y(y), vx(vx), vy(vy), ax(ax), ay(ay) {}

// Update particle
void Particle::update(double deltaTime, double solY, double coefficientRestitution) {
    // Mise à jour de la vitesse avec l'accélération
    vx += ax * deltaTime;
    vy += ay * deltaTime;

    // Mise à jour de la position avec la vitesse
    x += vx * deltaTime;
    y += vy * deltaTime;

    // Gestion des collisions avec le sol
    if (y <= solY) {
        y = solY;
        vy = -vy * coefficientRestitution; // Inversion de la vitesse avec restitution
    }
}

// Print particle state
void Particle::printState(double currentTime) const {
    std::cout << "Temps: " << currentTime << "s, Position: (" << x << ", " << y << ")\n";
}

// Detect if particle is at rest
bool Particle::isAtRest(double solY) const {
    return abs(y-solY) < 0.01 && abs(vy) < 0.01;
}
