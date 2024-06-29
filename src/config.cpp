#include "config.h"

bool readConfig(const std::string& filename, Config& config) {
    YAML::Node yaml = YAML::LoadFile(filename);

    // Load particles
    for (const auto& particleNode : yaml["particles"]) {
        std::array<double, 2> position = particleNode["position"].as<std::array<double, 2>>();
        std::array<double, 2> velocity = particleNode["velocity"].as<std::array<double, 2>>();
        double radius = particleNode["radius"].as<double>();
        double mass = particleNode["mass"].as<double>();
        Particle particle(position, velocity, radius, mass);
        config.particles.push_back(particle);
    }

    // Random particles
    config.rndParticle_numbers = yaml["randomParticles"]["numbers"].as<int>();
    config.rndParticle_maxVelocityX = yaml["randomParticles"]["maxVelocityX"].as<double>();
    config.rndParticle_maxVelocityY = yaml["randomParticles"]["maxVelocityY"].as<double>();
    config.rndParticle_minRadius = yaml["randomParticles"]["minRadius"].as<double>();
    config.rndParticle_maxRadius = yaml["randomParticles"]["maxRadius"].as<double>();
    config.rndParticle_minMass = yaml["randomParticles"]["minMass"].as<double>();
    config.rndParticle_maxMass = yaml["randomParticles"]["maxMass"].as<double>();

    // Load box
    double xOrigin = yaml["box"]["xOrigin"].as<double>();
    double yOrigin = yaml["box"]["yOrigin"].as<double>();
    double length = yaml["box"]["length"].as<double>();
    double height = yaml["box"]["height"].as<double>();
    config.box = Box(xOrigin, yOrigin, length, height);

    // Load circle
    double centerX = yaml["circle"]["centerX"].as<double>();
    double centerY = yaml["circle"]["centerY"].as<double>();
    double radius = yaml["circle"]["radius"].as<double>();
    config.circle = Circle(centerX, centerY, radius);

    // Load simulation parameters
    config.deltaTime = yaml["simulation"]["deltaTime"].as<double>();
    config.applyGravity = yaml["simulation"]["applyGravity"].as<bool>();
    config.globalAcceleration = yaml["simulation"]["globalAcceleration"].as<std::array<double, 2>>();
    config.coefficientRestitution = yaml["simulation"]["coefficientRestitution"].as<double>();

    // Load visualization parameters
    config.scaleFactorPixels = yaml["visualization"]["scaleFactorPixels"].as<double>();

    return true;
}