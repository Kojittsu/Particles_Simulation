#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include "particle.h"
#include <fstream>
#include <string>

class Universe {
public:
    Universe(const std::vector<Particle>& particles, double deltaTime, double solY, double coefficientRestitution);
    void run(int steps, const std::string& filename = "");

private:
    double deltaTime;
    double solY;
    double coefficientRestitution;
    std::vector<Particle> particles;
};

#endif // UNIVERSE_H
