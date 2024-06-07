#include "particle.h"

// Constructor
Particle::Particle(const std::array<double, 2>& position, const std::array<double, 2>& velocity, const double radius)
    : position(position), velocity(velocity), radius(radius) {}

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

// Setters for acceleration
void Particle::setAX(double ax) {acceleration[0] = ax;}
void Particle::setAY(double ay) {acceleration[1] = ay;}

// Getters for radius
double Particle::getRadius() const {return radius;}

// Update particle
void Particle::update(double deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}

// Print particle state
void Particle::printState(double currentTime) const {
    std::cout << "Temps: " << currentTime << "s, Position: (" << position[0] << ", " << position[1] << ")\n";
}