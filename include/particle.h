#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <cmath>
#include <array>
#include "array.h"

class Particle {
public:
    // Constructor
    Particle(const std::array<double, 2>& position, const std::array<double, 2>& velocity, const std::array<double, 2>& acceleration, const double radius, const double mass, const std::array<int, 3>& color);
    
    // Getters for position
    std::array<double, 2> getPosition() const;
    double getX() const;
    double getY() const;

    // Setters for position
    void setPosition(const std::array<double, 2>& position);
    void setX(double x);
    void setY(double y);

    // Getters for velocity
    std::array<double, 2> getVelocity() const ;
    double getVX() const;
    double getVY() const;

    // Setters for velocity
    void setVelocity(const std::array<double, 2>& velocity);
    void setVX(double vx);
    void setVY(double vy);

    // Getters for acceleration
    std::array<double, 2> getAcceleration() const;

    // Setters for acceleration
    void setAcceleration(const std::array<double, 2>& acceleration);
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
    std::array<double, 2> m_position;
    std::array<double, 2> m_velocity;
    std::array<double, 2> m_acceleration;
    double m_radius;
    double m_mass;
    std::array<int, 3> m_color;  // RGB particle color
};

#endif
