#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <fstream>
#include <string>
#include "particle.h"
#include "box.h"

class Universe {
public:
    Universe(const std::vector<Particle>& particles, double deltaTime);
    void run(int steps, const std::string& filename = "");
    void handleBoxCollision(Particle &particle, const Box &box);

private:
    double deltaTime;
    double coefficientRestitution;
    std::vector<Particle> particles;
};

#endif // UNIVERSE_H
