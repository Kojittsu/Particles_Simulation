#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "box.h"

#include "particle.h"
#include "universe.h"
#include "SFML_functions.h"

using json = nlohmann::json;

struct Config {
    std::vector<Particle> particles;
    Box box = Box();
    double delta_time;
    int step_numbers;
    double coefficientRestitution;
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
        double radius = particleJson["radius"];
        Particle particle(position, velocity, acceleration, radius);
        config.particles.push_back(particle);
    }

    json boxJson = configJson["box"];
    config.box = Box(boxJson["min_x"], boxJson["max_x"], boxJson["min_y"], boxJson["max_y"]);

    config.delta_time = configJson["simulation"]["delta_time"];
    config.step_numbers = configJson["simulation"]["step_numbers"];
    config.coefficientRestitution = configJson["simulation"]["coefficientRestitution"];

    return true;
}

std::vector<std::vector<Coordinate>> readParticlesMovements(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::map<int, std::vector<Coordinate>> particleMap;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 4) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue; // skip invalid lines
        }

        double time = std::stod(tokens[0]);
        int particle_number = std::stoi(tokens[1]);
        double x = std::stod(tokens[2]);
        double y = std::stod(tokens[3]);

        Coordinate coord(time, x, y);
        particleMap[particle_number].push_back(coord);
    }

    std::vector<std::vector<Coordinate>> particleMovements;
    for (auto& pair : particleMap) {
        particleMovements.push_back(std::move(pair.second));
    }

    return particleMovements;
}

int main() {
    // Read configuration
    Config config;
    if (!readConfig("config.json", config)) {
        return 1;
    }

    // Create and run universe
    Universe universe(config.particles, config.box, config.coefficientRestitution, config.delta_time);
    universe.run(config.step_numbers, "data.csv");

    // Read particles movements data in file
    std::vector<std::vector<Coordinate>> particlesMovements = readParticlesMovements("data.csv");

    // Display simulation in SFML
    int scaleFactorPixels = 50;
    int windowLength = scaleFactorPixels*config.box.getLength(); 
    int windowHeight = scaleFactorPixels*config.box.getHeight(); 
    display_universe_SFML(particlesMovements, config.box, config.particles[0].getRadius(), windowLength, windowHeight);

    return 0;
}
