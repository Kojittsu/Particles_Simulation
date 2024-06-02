#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <fstream>
#include <string>
#include "particle.h"
#include "box.h"
#include "config.h"
#include "utils.h"

class Universe {
public:
    Universe(const Config& config);
    void run(const std::string& filename = "");
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
    int stepNumbers;
    
};

#endif // UNIVERSE_H
