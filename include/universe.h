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
    void saveStep(std::ofstream &file, int stepNumber);
    void addParticle(Particle &particle);
    void addRndParticle(double maxVelocityX, double maxVelocityY, double minRadius, double maxRadius, double minMass, double maxMass);
    void applyAccelerationToParticles(std::array<double, 2> &globalAcceleration);
    void computeGravitationalForces();
    void handleParticleCollisions();
    void handleBoxCollision(Particle &particle, double coefficientRestitution);
    void handleCircleCollision(Particle &particle, double coefficientRestitution);
    std::vector<Particle> const& getParticles() const;
    double getRunTime() const;
    void setRunTime(double newRunTime);

    // Box
    const double boxOriginX;
    const double boxOriginY;
    const double boxLength;
    const double boxHeight;

    // Circle
    const double circleX;
    const double circleY;
    const double circleRadius;

    // Visualization
    const double scaleFactorPixels;

private:
    std::vector<Particle> particles;
    double coefficientRestitution;
    double deltaTime;
    bool applyGravity;
    std::array<double, 2> globalAcceleration;
    double speedFactor;
    const std::string dataFileName;
    const double G = 6.67430e-11; // gravitational constant
    double runTime = 0;

};

#endif // UNIVERSE_H
