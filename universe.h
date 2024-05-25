#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include "particle.h"
#include <fstream>
#include <string>

class Universe {
public:
    Universe(const std::vector<Particle>& particles, double deltaTime);
    void run(int steps, const std::string& filename = "");
    void handleBoxCollision(Particle &particle,double xMin, double xMax, double yMin, double yMax);

private:
    double deltaTime;
    double coefficientRestitution;
    std::vector<Particle> particles;
};

#endif // UNIVERSE_H
