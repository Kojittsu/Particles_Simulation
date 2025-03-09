#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <fstream>
#include <string>

#include "particle.h"
#include "config.h"
#include "utils.h"

class Universe {
public:
    Universe(const Config& config);
    void makeStep();
    void saveStep(std::ofstream& file, int stepNumber);
    void addParticle(const Particle& particle);
    void addRndParticle();
    void applyAccelerationToParticles(const std::array<double, 3>& accelerationContribution);
    void computeGravitationalForces();
    void handleParticleCollisions();
    void handleBoxCollision(Particle& particle);
    std::vector<Particle> const& getParticles() const;
    void toggleGravity();

    const Config m_config;

    // Simulation parameters
    double m_runTime = 0;

private:
    std::vector<Particle> m_particles;
    bool m_applyGravity;
    std::array<double, 3> m_globalAcceleration;
    double m_speedFactor;
    const double m_G = 6.67430e-11; // gravitational constant

};

#endif // UNIVERSE_H
