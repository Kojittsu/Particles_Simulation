#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <cmath>

class Particle {
public:
    // Constructor
    Particle(double x, double y, double vx, double vy, double ax, double ay);

    // Getter for x
    double getX() const;
    
    // Getter for y
    double getY() const;

    // Update particle
    void update(double deltaTime, double solY, double coefficientRestitution);

    // Print particle state
    void printState(double currentTime) const;

private:
    double x, y;       // Position
    double vx, vy;     // Speed
    double ax, ay;     // Acceleration
};

#endif // PARTICLE_H
