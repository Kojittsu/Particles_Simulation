#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <cmath>
#include <array>
#include "array.h"

class Particle {
public:
    // Constructor
    Particle(const std::array<double, 2>& position, const std::array<double, 2>& velocity, const double radius, const double mass, const std::array<int, 3>& color);
    
    // Getters for position
    std::array<double, 2> getPosition() const;
    double getX() const;
    double getY() const;

    // Setters for position
    void setPosition(std::array<double, 2> newPosition);
    void setX(double x);
    void setY(double y);

    // Getters for velocity
    std::array<double, 2> getVelocity() const ;
    double getVX() const;
    double getVY() const;

    // Setters for velocity
    void setVelocity(std::array<double, 2> newVelocity);
    void setVX(double vx);
    void setVY(double vy);

    // Getters for acceleration
    std::array<double, 2> getAcceleration() const;

    // Setters for acceleration
    void setAcceleration(std::array<double, 2> newAcceleration);
    void setAX(double ax);
    void setAY(double ay);

    // Getters for radius
    double getRadius() const;

    // Getters for mass
    double getMass() const;

    // Getters for color
    std::array<int, 3> getColor() const;

    // Update particle
    void update(double deltaTime);

private:
    std::array<double, 2> position;
    std::array<double, 2> velocity;
    std::array<double, 2> acceleration = {0.0, 0.0};
    double radius;
    double mass;
    std::array<int, 3> color;  // RGB particle color
};

#endif // PARTICLE_H
