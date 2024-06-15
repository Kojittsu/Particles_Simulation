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
    void run(const std::string& filename = "");
    void makeStep();
    void saveStep(std::ofstream &file, int stepNumber);
    void addParticle(Particle &particle);
    void addRndParticle(double maxVelocityX, double maxVelocityY, double minRadius, double maxRadius, double minMass, double maxMass);
    void applyAccelerationToParticles(double ax, double ay);
    void computeGravitationalForces();
    std::vector<double> getParticlesRadius();
    void handleParticleCollisions();
    void handleBoxCollision(Particle &particle, double coefficientRestitution);
    void handleCircleCollision(Particle &particle, double coefficientRestitution);

private:
    std::vector<Particle> particles;
    Box box;
    Circle circle;
    double coefficientRestitution;
    double deltaTime;
    double simulationTime;
    bool applyGravity;
    double AccelerationX;
    double AccelerationY;
    const double G = 6.67430e-11; // gravitational constant
    
};

#endif // UNIVERSE_H
