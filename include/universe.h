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
    void addRndParticle(double maxVelocityX, double maxVelocityY, double minRadius, double maxRadius, double minMass, double maxMass);
    void applyAccelerationToParticles(const std::array<double, 2>& accelerationContribution);
    void computeGravitationalForces();
    void handleParticleCollisions();
    void handleBoxCollision(Particle& particle);
    void handleCircleCollision(Particle& particle);
    std::vector<Particle> const& getParticles() const;

    // Box
    const double m_boxOriginX;
    const double m_boxOriginY;
    const double m_boxLength;
    const double m_boxHeight;

    // Circle
    const double m_circleX;
    const double m_circleY;
    const double m_circleRadius;

    // Visualization
    const double m_scaleFactorPixels;

    // Simulation parameters
    double m_runTime = 0;

private:
    std::vector<Particle> m_particles;
    double m_coefficientRestitution;
    double m_deltaTime;
    bool m_applyGravity;
    std::array<double, 2> m_globalAcceleration;
    double m_speedFactor;
    const std::string m_dataFileName;
    const double m_G = 6.67430e-11; // gravitational constant

};

#endif // UNIVERSE_H
