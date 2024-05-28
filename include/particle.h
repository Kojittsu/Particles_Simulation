#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <cmath>
#include <array>

class Particle {
public:
    // Constructor
    Particle(const std::array<double, 2>& position, const std::array<double, 2>& velocity, const std::array<double, 2>& acceleration);
    
    // Getters for position
    double getX() const;
    double getY() const;

    // Setters for position
    void setX(double x);
    void setY(double y);

    // Getters for velocity
    double getVX() const;
    double getVY() const;

    // Setters for velocity
    void setVX(double vx);
    void setVY(double vy);

    // Update particle
    void update(double deltaTime);

    // Print particle state
    void printState(double currentTime) const;

private:
    std::array<double, 2> position;
    std::array<double, 2> velocity;
    std::array<double, 2> acceleration;
};

#endif // PARTICLE_H
