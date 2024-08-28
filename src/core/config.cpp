#include "config.h"

bool readConfig(const std::string& filename, Config& config) {
    YAML::Node yaml = YAML::LoadFile(filename);

    // Random particles
    config.rndParticle_numbers      = yaml["randomParticles"]["numbers"].as<int>();
    config.rndParticle_maxVelocityX = yaml["randomParticles"]["maxVelocityX"].as<double>();
    config.rndParticle_maxVelocityY = yaml["randomParticles"]["maxVelocityY"].as<double>();
    config.rndParticle_maxVelocityZ = yaml["randomParticles"]["maxVelocityZ"].as<double>();
    config.rndParticle_minRadius    = yaml["randomParticles"]["minRadius"].as<double>();
    config.rndParticle_maxRadius    = yaml["randomParticles"]["maxRadius"].as<double>();
    config.rndParticle_minMass      = yaml["randomParticles"]["minMass"].as<double>();
    config.rndParticle_maxMass      = yaml["randomParticles"]["maxMass"].as<double>();

    // Load box
    config.boxOriginX = yaml["box"]["xOrigin"].as<double>();
    config.boxOriginY = yaml["box"]["yOrigin"].as<double>();
    config.boxOriginZ = yaml["box"]["zOrigin"].as<double>();
    config.boxLength  = yaml["box"]["length"].as<double>();
    config.boxHeight  = yaml["box"]["height"].as<double>();
    config.boxDepth  = yaml["box"]["depth"].as<double>();

    // Load simulation parameters
    config.deltaTime              = yaml["simulation"]["deltaTime"].as<double>();
    config.applyGravity           = yaml["simulation"]["applyGravity"].as<bool>();
    config.globalAcceleration     = yaml["simulation"]["globalAcceleration"].as<std::array<double, 3>>();
    config.coefficientRestitution = yaml["simulation"]["coefficientRestitution"].as<double>();
    config.dataFileName           = yaml["simulation"]["dataFileName"].as<std::string>();

    // Load visualization parameters
    config.speedFactor       = yaml["visualization"]["speedFactor"].as<double>();

    // Load particles
    for (const auto& particleNode : yaml["particles"]) {
        std::array<double, 3> position = particleNode["position"].as<std::array<double, 3>>();
        std::array<double, 3> velocity = particleNode["velocity"].as<std::array<double, 3>>();
        double radius                  = particleNode["radius"].as<double>();
        double mass                    = particleNode["mass"].as<double>();
        std::array<int, 3> color       = particleNode["color"].as<std::array<int, 3>>();
        std::string name               = particleNode["name"].as<std::string>();

        Particle particle(position, velocity, config.globalAcceleration, radius, mass, color, name);
        config.particles.push_back(particle);
    }

    return true;
}