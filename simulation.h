#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "particle.h"
#include <fstream>
#include <string>

class Simulation {
public:
    Simulation(const std::vector<Particle>& particles, double gravite, double deltaTime, double solY, double coefficientRestitution);
    void run(int steps, const std::string& filename = "");

private:
    double gravite;
    double deltaTime;
    double solY;
    double coefficientRestitution;
    std::vector<Particle> particles;

    bool allParticlesAtRest() const;
};

#endif // SIMULATION_H
