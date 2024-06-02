#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <fstream>
#include <string>
#include "particle.h"
#include "box.h"

class Universe {
public:
    Universe(const std::vector<Particle>& particles, const Box &box, const double coefficientRestitution, double deltaTime);
    void run(int steps, const std::string& filename = "");
    void makeStep();
    void saveStep(std::ofstream &file, int stepNumber);
    void addRndParticle(double maxVelocity, double minRadius, double maxRadius);
    std::vector<double> getParticlesRadius();
    void handleBoxCollision(Particle &particle, double coefficientRestitution);

private:
    std::vector<Particle> particles;
    Box box;
    double coefficientRestitution;
    double deltaTime;
    
};

#endif // UNIVERSE_H
