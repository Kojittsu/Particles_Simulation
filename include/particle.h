#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <cmath>
#include <array>
#include <deque>
#include "array.h"

class Particle {
public:
    // Constructor
    Particle(
        const std::array<double, 3>& position,
        const std::array<double, 3>& velocity,
        const std::array<double, 3>& acceleration,
        const double radius, const double mass,
        const std::array<int, 3>& color,
        const std::string& name = ""
        );
    
    // Getters for position
    std::array<double, 3> getPosition() const;
    double getX() const;
    double getY() const;
    double getZ() const;

    // Setters for position
    void setPosition(const std::array<double, 3>& position);
    void setX(double x);
    void setY(double y);
    void setZ(double z);

    // Getters for velocity
    std::array<double, 3> getVelocity() const ;
    double getVX() const;
    double getVY() const;
    double getVZ() const;

    // Setters for velocity
    void setVelocity(const std::array<double, 3>& velocity);
    void setVX(double vx);
    void setVY(double vy);
    void setVZ(double vz);

    // Getters for acceleration
    std::array<double, 3> getAcceleration() const;

    // Setters for acceleration
    void setAcceleration(const std::array<double, 3>& acceleration);
    void setAX(double ax);
    void setAY(double ay);
    void setAZ(double az);

    // Getters for radius
    double getRadius() const;

    // Getters for mass
    double getMass() const;

    // Getters for color
    std::array<int, 3> getColor() const;

    // Update particle
    void update(double deltaTime);

    void addTrailPoint(const std::array<double, 3>& point);

    const std::deque<std::array<double, 3>>& getTrail() const;

private:
    std::array<double, 3> m_position;
    std::array<double, 3> m_velocity;
    std::array<double, 3> m_acceleration;
    double m_radius;
    double m_mass;
    std::array<int, 3> m_color;

    std::deque<std::array<double, 3>> m_trail;
    static constexpr size_t m_maxTrailLength = 5000;

public:
    const std::string m_name;
};

#endif
