#include <SFML/Graphics.hpp>

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "config.h"
#include "box.h"
#include "particle.h"
#include "universe.h"
#include "SFML_functions.h"

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
        int particleNumber = std::stoi(tokens[1]);
        double x = std::stod(tokens[2]);
        double y = std::stod(tokens[3]);

        Coordinate coord(time, x, y);
        particleMap[particleNumber].push_back(coord);
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

    // Create universe
    Universe universe(config);

    // Add random particles
    double maxVelocity = 5.0;
    double minRadius = 0.1;
    double maxRadius = 0.2;
    for(int i=0; i< 100; i++){universe.addRndParticle(maxVelocity, minRadius, maxRadius);}
    
    // Run universe
    universe.run("data.csv");

    // Read particles movements data in file
    std::vector<std::vector<Coordinate>> particlesMovements = readParticlesMovements("data.csv");

    // Display simulation in SFML
    int scaleFactorPixels = 50;
    std::vector<double> particlesRadius = universe.getParticlesRadius(); // Get all radius
    display_universe_SFML(particlesMovements, config.box, particlesRadius, scaleFactorPixels);

    return 0;
}
