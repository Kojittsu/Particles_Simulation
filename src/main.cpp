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

std::vector<Coordinate> readFileData(){
    // Vecteur pour stocker les coordonnées
    std::vector<Coordinate> coordinates;
    // Open file
    std::ifstream file("data.csv");
    if (file.is_open()) {
        std::string line;

        // Read data in file
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            Coordinate coord;
            char comma;
            ss >> coord.time >> comma >> coord.x >> comma >> coord.y;
            coordinates.push_back(coord);
        }
    // Close file
    file.close();
    }
    return coordinates;
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

    std::vector<Coordinate> coordinates = readFileData();

    display_universe_SFML(coordinates, config.box, config.particles[0].getRadius(), 500, 500);

    return 0;
}
