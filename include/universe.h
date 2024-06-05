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
    void addRndParticle(double maxVelocityX, double maxVelocityY, double minRadius, double maxRadius);
    void applyGravityToParticles(double ax, double ay);
    std::vector<double> getParticlesRadius();
    void handleParticleCollisions(double coefficientRestitution);
    void handleBoxCollision(Particle &particle, double coefficientRestitution);
    void handleCircleCollision(Particle &particle, double coefficientRestitution);

private:
    std::vector<Particle> particles;
    Box box;
    Circle circle;
    double coefficientRestitution;
    double deltaTime;
    int stepNumbers;
    
};

#endif // UNIVERSE_H
