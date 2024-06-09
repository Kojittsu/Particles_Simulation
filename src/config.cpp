#include "config.h"

bool readConfig(const std::string& filename, Config& config) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config file " << filename << std::endl;
        return false;
    }

    json configJson;
    file >> configJson;

    if (configJson.contains("particles")) {
        for (const auto& particleJson : configJson["particles"]) {
            std::array<double, 2> position = particleJson.value("position", std::array<double, 2>{0.0, 0.0});
            std::array<double, 2> velocity = particleJson.value("velocity", std::array<double, 2>{0.0, 0.0});
            double radius = particleJson.value("radius", 1.0);
            double mass = particleJson.value("mass", 1.0);
            Particle particle(position, velocity, radius, mass);
            config.particles.push_back(particle);
        }
    }

    if (configJson.contains("box")) {
        json boxJson = configJson["box"];
        config.box = Box(
            boxJson.value("xOrigin", 0.0),
            boxJson.value("yOrigin", 0.0),
            boxJson.value("length", 0.0),
            boxJson.value("height", 0.0)
        );
    }

    if (configJson.contains("circle")) {
        json circleJson = configJson["circle"];
        config.circle = Circle(
            circleJson.value("centerX", 0.0),
            circleJson.value("centerY", 0.0),
            circleJson.value("radius", 1.0)
        );
    }

    if (configJson.contains("simulation")) {
        json simulationJson = configJson["simulation"];
        config.deltaTime = simulationJson.value("deltaTime", 0.01);
        config.stepNumbers = simulationJson.value("stepNumbers", 1000);
        config.AccelerationX = simulationJson.value("AccelerationX", 0.0);
        config.AccelerationY = simulationJson.value("AccelerationY", 0.0);
        config.coefficientRestitution = simulationJson.value("coefficientRestitution", 0.9);
    } else {
        config.deltaTime = 0.01;
        config.stepNumbers = 1000;
        config.AccelerationX = 0.0;
        config.AccelerationY = 0.0;
        config.coefficientRestitution = 0.9;
    }

    if (configJson.contains("visualization")) {
        json visualizationJson = configJson["visualization"];
        config.speedFactor = visualizationJson.value("speedFactor", 1.0);
        config.scaleFactorPixels = visualizationJson.value("scaleFactorPixels", 1.0);
    } else {
        config.speedFactor = 1.0;
        config.scaleFactorPixels = 1.0;
    }

    return true;
}