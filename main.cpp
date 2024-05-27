#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <nlohmann/json.hpp>
#include "particle.h"
#include "universe.h"

using json = nlohmann::json;

struct Config {
    std::vector<Particle> particles;
    Box box = Box();
    double delta_time;
    int step_numbers;
};

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
        Particle particle(position, velocity, acceleration);
        config.particles.push_back(particle);
    }

    json boxJson = configJson["box"];
    config.box = Box(boxJson["min_x"], boxJson["max_x"], boxJson["min_y"], boxJson["max_y"]);

    config.delta_time = configJson["simulation"]["delta_time"];
    config.step_numbers = configJson["simulation"]["step_numbers"];

    return true;
}



int main() {
    // Read configuration
    Config config;
    if (!readConfig("config.json", config)) {
        return 1;
    }

    // Create and run universe
    double coefficientRestitution = 0.7;
    Universe universe(config.particles, config.box, coefficientRestitution, config.delta_time);
    universe.run(config.step_numbers, "data.csv");

    return 0;
}
