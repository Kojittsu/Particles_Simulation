#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <yaml-cpp/yaml.h>

#include "particle.h"
#include "box.h"

struct Config {
    std::vector<Particle> particles;

    std::vector<Box> boxes;
    
    double deltaTime;
    bool applyGravity;
    std::array<double, 3> globalAcceleration;
    double coefficientRestitution;
    std::string dataFileName;
    
    double speedFactor;
    double scaleFactor;
};

bool readConfig(const std::string& filename, Config& config);

#endif
