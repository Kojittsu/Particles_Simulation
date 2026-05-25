#include "particle.h"

Particle::Particle(const std::array<double, 3>& position,
    const std::array<double, 3>& velocity,
    const std::array<double, 3>& acceleration,
    const double radius, const double mass,
    const std::array<float, 3>& color,
    const std::string& name
    ):
      position_(position),
      velocity_(velocity),
      acceleration_(acceleration),
      radius_(radius),
      mass_(mass),
      color_(color),
      name_(name)
{
    // Validate the parameters
    if (radius < 0) {
        throw std::invalid_argument("Radius cannot be negative");
    }
    if (mass < 0) {
        throw std::invalid_argument("Mass cannot be negative");
    }
    // Validate the color components
    for (float component : color) {
        if (component < 0 || component > 1) {
            throw std::invalid_argument("Color components must be in the range [0,1]");
        }
    }
}

void Particle::update(const double deltaTime) {
    velocity_ += acceleration_ * deltaTime;
    position_ += velocity_ * deltaTime;

    // add new position to trail
    addTrailPoint(position_);
}

void Particle::addTrailPoint(const std::array<double, 3>& point) {
    trail_.push_back(point);
    if (trail_.size() > maxTrailLength_)
        trail_.pop_front();
}
