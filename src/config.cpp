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
    // config.stepNumbers = yaml["simulation"]["stepNumbers"].as<int>();
    config.simulationTime = yaml["simulation"]["simulationTime"].as<double>();
    config.applyGravity = yaml["simulation"]["applyGravity"].as<bool>();
    config.AccelerationX = yaml["simulation"]["AccelerationX"].as<double>();
    config.AccelerationY = yaml["simulation"]["AccelerationY"].as<double>();
    config.coefficientRestitution = yaml["simulation"]["coefficientRestitution"].as<double>();

    // Load visualization parameters
    config.speedFactor = yaml["visualization"]["speedFactor"].as<double>();
    config.scaleFactorPixels = yaml["visualization"]["scaleFactorPixels"].as<double>();
    config.drawTrails = yaml["visualization"]["drawTrails"].as<bool>();

    return true;
}