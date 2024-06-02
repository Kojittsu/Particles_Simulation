#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include "particle.h"
#include "box.h"

struct Config {
    std::vector<Particle> particles;
    Box box = Box();
    double deltaTime;
    int stepNumbers;
    double coefficientRestitution;
};

#endif // CONFIG_H
