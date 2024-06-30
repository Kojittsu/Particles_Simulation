#include "particle.h"

// Constructor
Particle::Particle(const std::array<double, 2>& position, const std::array<double, 2>& velocity, const double radius, const double mass, const std::array<int, 3>& color)
    : 
      m_position(position),
      m_velocity(velocity),
      m_radius(radius),
      m_mass(mass),
      m_color(color)
    {}

// Getters for position
std::array<double, 2> Particle::getPosition() const {return m_position;}
double Particle::getX() const {return m_position[0];}
double Particle::getY() const {return m_position[1];}

// Setters for position
void Particle::setPosition(std::array<double, 2> position) {m_position = position;}
void Particle::setX(double x) {m_position[0] = x;}
void Particle::setY(double y) {m_position[1] = y;}

// Getters for velocity
std::array<double, 2> Particle::getVelocity() const {return m_velocity;}
double Particle::getVX() const {return m_velocity[0];}
double Particle::getVY() const {return m_velocity[1];}

// Setters for velocity
void Particle::setVelocity(std::array<double, 2> velocity) {m_velocity = velocity;}
void Particle::setVX(double vx) {m_velocity[0] = vx;}
void Particle::setVY(double vy) {m_velocity[1] = vy;}

// Getters for acceleration
std::array<double, 2> Particle::getAcceleration() const {return m_acceleration;}

// Setters for acceleration
void Particle::setAcceleration(std::array<double, 2> acceleration) {m_acceleration = acceleration;}
void Particle::setAX(double ax) {m_acceleration[0] = ax;}
void Particle::setAY(double ay) {m_acceleration[1] = ay;}

// Getters for radius
double Particle::getRadius() const {return m_radius;}

// Getters for mass
double Particle::getMass() const {return m_mass;}

// Getters for color
std::array<int, 3> Particle::getColor() const {return m_color;}

// Update particle
void Particle::update(double deltaTime) {
    m_velocity += m_acceleration * deltaTime;
    m_position += m_velocity * deltaTime;
}