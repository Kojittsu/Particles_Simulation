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
            Particle particle(position, velocity, radius);
            config.particles.push_back(particle);
        }
    }

    if (configJson.contains("box")) {
        json boxJson = configJson["box"];
        config.box = Box(
            boxJson.value("xMin", 0.0),
            boxJson.value("xMax", 1.0),
            boxJson.value("yMin", 0.0),
            boxJson.value("yMax", 1.0)
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
        config.coefficientRestitution = simulationJson.value("coefficientRestitution", 0.9);
        config.scaleFactorPixels = simulationJson.value("scaleFactorPixels", 50);
    } else {
        config.deltaTime = 0.01; // default value
        config.stepNumbers = 1000; // default value
        config.coefficientRestitution = 0.9; // default value
    }

    return true;
}