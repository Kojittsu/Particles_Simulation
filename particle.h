#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <cmath>
#include <array>

class Particle {
public:
    // Constructor
    Particle(const std::array<double, 2>& position, const std::array<double, 2>& velocity, const std::array<double, 2>& acceleration);
    // Getter for x
    double getX() const;
    
    // Getter for y
    double getY() const;

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
