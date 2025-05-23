#include "particle.h"

// Constructor
Particle::Particle(const std::array<double, 3>& position,
    const std::array<double, 3>& velocity,
    const std::array<double, 3>& acceleration,
    const double radius, const double mass,
    const std::array<int, 3>& color,
    const std::string& name
    ): 
      m_position(position),
      m_velocity(velocity),
      m_acceleration(acceleration),
      m_radius(radius),
      m_mass(mass),
      m_color(color),
      m_name(name)
{
    // Validate the parameters
    if (radius < 0) {
        throw std::invalid_argument("Radius cannot be negative");
    }
    if (mass < 0) {
        throw std::invalid_argument("Mass cannot be negative");
    }
    // Validate the color components
    for (int component : color) {
        if (component < 0 || component > 255) {
            throw std::invalid_argument("Color components must be in the range [0, 255]");
        }
    }
}

// Getters for position
std::array<double, 3> Particle::getPosition() const {return m_position;}
double Particle::getX() const {return m_position[0];}
double Particle::getY() const {return m_position[1];}
double Particle::getZ() const {return m_position[2];}

// Setters for position
void Particle::setPosition(const std::array<double, 3>& position) {m_position = position;}
void Particle::setX(double x) {m_position[0] = x;}
void Particle::setY(double y) {m_position[1] = y;}
void Particle::setZ(double z) {m_position[2] = z;}

// Getters for velocity
std::array<double, 3> Particle::getVelocity() const {return m_velocity;}
double Particle::getVX() const {return m_velocity[0];}
double Particle::getVY() const {return m_velocity[1];}
double Particle::getVZ() const {return m_velocity[2];}

// Setters for velocity
void Particle::setVelocity(const std::array<double, 3>& velocity) {m_velocity = velocity;}
void Particle::setVX(double vx) {m_velocity[0] = vx;}
void Particle::setVY(double vy) {m_velocity[1] = vy;}
void Particle::setVZ(double vz) {m_velocity[2] = vz;}

// Getters for acceleration
std::array<double, 3> Particle::getAcceleration() const {return m_acceleration;}

// Setters for acceleration
void Particle::setAcceleration(const std::array<double, 3>& acceleration) {m_acceleration = acceleration;}
void Particle::setAX(double ax) {m_acceleration[0] = ax;}
void Particle::setAY(double ay) {m_acceleration[1] = ay;}
void Particle::setAZ(double az) {m_acceleration[2] = az;}

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

    // add new position to trail
    addTrailPoint(m_position);
}

void Particle::addTrailPoint(const std::array<double, 3>& point) {
    m_trail.push_back(point);
    if (m_trail.size() > m_maxTrailLength)
        m_trail.pop_front();
}

const std::deque<std::array<double, 3>>& Particle::getTrail() const { return m_trail; }