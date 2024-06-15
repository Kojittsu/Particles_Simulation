#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include "particle.h"
#include "box.h"
#include "circle.h"

struct Config {
    std::vector<Particle> particles;
    Box box = Box();
    Circle circle = Circle();
    double deltaTime;
    double simulationTime;
    bool applyGravity;
    double AccelerationX;
    double AccelerationY;
    double coefficientRestitution;
    double scaleFactorPixels;
    double speedFactor;
};

bool readConfig(const std::string& filename, Config& config);

#endif // CONFIG_H
