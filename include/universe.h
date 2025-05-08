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
    void handleBoxesCollision(Particle& particle);
    std::vector<Particle> const& getParticles() const;
    void toggleGravity();
    bool getIsGravity();


    // Simulation parameters
    double m_simuationTime = 0;
    bool m_isRunning = false;

private:
    const Config m_config;
    std::vector<Particle> m_particles;
    std::vector<Box> m_boxes;
    bool m_applyGravity;
    std::array<double, 3> m_globalAcceleration;
    double m_speedFactor;
    const double m_G = 6.67430e-11; // gravitational constant

};

#endif // UNIVERSE_H
