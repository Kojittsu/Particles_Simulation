#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include "particle.h"

struct Config {
    std::vector<Particle> particles;

    int rndParticle_numbers;
    double rndParticle_maxVelocityX;
    double rndParticle_maxVelocityY;
    double rndParticle_maxVelocityZ;
    double rndParticle_minRadius;
    double rndParticle_maxRadius;
    double rndParticle_minMass;
    double rndParticle_maxMass;
    
    double boxOriginX;
    double boxOriginY;
    double boxOriginZ;
    double boxLength;
    double boxHeight;
    double boxDepth;
    
    double deltaTime;
    bool applyGravity;
    std::array<double, 3> globalAcceleration;
    double coefficientRestitution;
    std::string dataFileName;
    
    double speedFactor;
};

bool readConfig(const std::string& filename, Config& config);

#endif
