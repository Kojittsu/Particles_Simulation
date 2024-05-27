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
    void make_step(int i);
    void save_step(std::ofstream &file, int step_number);
    void handleBoxCollision(Particle &particle, double coefficientRestitution);

private:
    double deltaTime;
    double coefficientRestitution;
    std::vector<Particle> particles;
    Box box;
};

#endif // UNIVERSE_H
