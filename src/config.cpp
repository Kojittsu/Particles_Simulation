#include "config.h"

bool readConfig(const std::string& filename, Config& config) {
    YAML::Node yaml = YAML::LoadFile(filename);

    // Load renderer parameters
    config.rendererConfig.speedFactor       = yaml["renderer"]["speedFactor"].as<double>();
    config.rendererConfig.scaleFactor       = yaml["renderer"]["scaleFactor"].as<double>();

    // Load universe parameters
    config.universeConfig.deltaTime              = yaml["universe"]["deltaTime"].as<double>();
    config.universeConfig.applyGravity           = yaml["universe"]["applyGravity"].as<bool>();
    config.universeConfig.globalAcceleration     = yaml["universe"]["globalAcceleration"].as<std::array<double, 3>>();
    config.universeConfig.coefficientRestitution = yaml["universe"]["coefficientRestitution"].as<double>();
    config.universeConfig.dataFileName           = yaml["universe"]["dataFileName"].as<std::string>();

    for (const auto& particleNode : yaml["particles"]) {
        std::array<double, 3> position = particleNode["position"].as<std::array<double, 3>>();
        std::array<double, 3> velocity = particleNode["velocity"].as<std::array<double, 3>>();
        double radius                  = particleNode["radius"].as<double>();
        double mass                    = particleNode["mass"].as<double>();
        std::array<int, 3> color       = particleNode["color"].as<std::array<int, 3>>();
        std::string name               = particleNode["name"].as<std::string>();

        Particle particle(position, velocity, config.universeConfig.globalAcceleration, radius, mass, color, name);
        config.universeConfig.particles.push_back(particle);
    }

    for (const auto& particleNode : yaml["boxes"]) {
        std::array<double, 3> boxOrigin = particleNode["origin"].as<std::array<double, 3>>();
        double boxLength = particleNode["length"].as<double>();
        double boxHeight = particleNode["height"].as<double>();
        double boxDepth = particleNode["depth"].as<double>();

        Box box(boxOrigin, boxLength, boxHeight, boxDepth);
        config.universeConfig.boxes.push_back(box);
    }

    return true;
}
