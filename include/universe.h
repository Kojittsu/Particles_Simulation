#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <fstream>
#include <string>
#include "particle.h"
#include "box.h"
#include "circle.h"
#include "config.h"
#include "utils.h"

class Universe {
public:
    Universe(const Config& config);
    void run();
    void makeStep();
    void saveStep(std::ofstream &file, int stepNumber);
    void addParticle(Particle &particle);
    void addRndParticle(double maxVelocityX, double maxVelocityY, double minRadius, double maxRadius, double minMass, double maxMass);
    void applyAccelerationToParticles(std::array<double, 2> &globalAcceleration);
    void computeGravitationalForces();
    void handleParticleCollisions();
    void handleBoxCollision(Particle &particle, double coefficientRestitution);
    void handleCircleCollision(Particle &particle, double coefficientRestitution);
    Circle getCircle() const;
    Box getBox() const;
    std::vector<Particle> const& getParticles() const;
    double getRunTime() const;

private:
    std::vector<Particle> particles;
    Box box;
    Circle circle;
    double coefficientRestitution;
    double deltaTime;
    // double simulationTime;
    bool applyGravity;
    std::array<double, 2> globalAcceleration;
    double scaleFactorPixels;
    const std::string dataFileName;
    const double G = 6.67430e-11; // gravitational constant
    double runTime = 0;
    
};

#endif // UNIVERSE_H
