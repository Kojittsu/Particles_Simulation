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

// Structure to store space and time coordinates
struct Coordinate {
    double time;
    double x;
    double y;
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


int main() {
    // Read configuration
    Config config;
    if (!readConfig("config.json", config)) {
        return 1;
    }

    // Create and run universe
    Universe universe(config.particles, config.box, config.coefficientRestitution, config.delta_time);
    universe.run(config.step_numbers, "data.csv");

    // Open file
    std::ifstream file("data.csv");
    if (!file.is_open()) {
        return -1;
    }

    // Vecteur pour stocker les coordonnées
    std::vector<Coordinate> coordinates;
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

    // Create SFML windows
    int window_length = 1920;
    int window_height = 1080;
    sf::RenderWindow window(sf::VideoMode(window_length, window_height), "Particle Movement", sf::Style::Fullscreen);

    //Create borders
    sf::VertexArray borders = compute_border(window_length, window_height);

    // Create particle
    sf::CircleShape particle(10);
    particle.setFillColor(sf::Color::Red);

    // Index pour suivre la position actuelle de la particule
    std::size_t index = 0;
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Mise à jour de la position de la particule en fonction du temps écoulé
        if (index < coordinates.size() && clock.getElapsedTime().asSeconds() >= coordinates[index].time) {
            std::array<double, 2> SFML_coord = coord_To_SFML_Coord(coordinates[index].x, coordinates[index].y, config.box, window_length, window_height);
            particle.setPosition(SFML_coord[0], SFML_coord[1]);
            index++;
        }

        window.clear();
        window.draw(particle);
        window.draw(borders);
        window.display();
    }

    return 0;
}
