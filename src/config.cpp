#include "config.h"

bool readConfig(const std::string& filename, Config& config) {
    YAML::Node yaml = YAML::LoadFile(filename);

    // Load boxes
    for (const auto& particleNode : yaml["boxes"]) {
        std::array<double, 3> boxOrigin = particleNode["origin"].as<std::array<double, 3>>();
        double boxLength = particleNode["length"].as<double>();
        double boxHeight = particleNode["height"].as<double>();
        double boxDepth = particleNode["depth"].as<double>();

        Box box(boxOrigin, boxLength, boxHeight, boxDepth);
        config.boxes.push_back(box);
    }

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