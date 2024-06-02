#include "config.h"

bool readConfig(const std::string& filename, Config& config) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config file " << filename << std::endl;
        return false;
    }

    json configJson;
    file >> configJson;

    for (const auto& particleJson : configJson["particles"]) {
        std::array<double, 2> position = particleJson["position"];
        std::array<double, 2> velocity = particleJson["velocity"];
        std::array<double, 2> acceleration = particleJson["acceleration"];
        double radius = particleJson["radius"];
        Particle particle(position, velocity, acceleration, radius);
        config.particles.push_back(particle);
    }

    json boxJson = configJson["box"];
    config.box = Box(boxJson["xMin"], boxJson["xMax"], boxJson["yMin"], boxJson["yMax"]);

    json circleJson = configJson["circle"];
    config.circle = Circle(circleJson["centerX"], circleJson["centerY"], circleJson["radius"]);

    config.deltaTime = configJson["simulation"]["deltaTime"];
    config.stepNumbers = configJson["simulation"]["stepNumbers"];
    config.coefficientRestitution = configJson["simulation"]["coefficientRestitution"];

    return true;
}