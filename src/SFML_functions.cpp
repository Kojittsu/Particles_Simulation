#include <SFML/Graphics.hpp>
#include "SFML_functions.h"

std::array<double, 2> coord_To_SFML_Coord(const double x, const double y, const Box &box, int window_length, int window_height){
    std::array<double, 2> SFML_coord;
    SFML_coord[0] = x * window_length / box.getLength();
    SFML_coord[1] = window_height - (y * window_height / box.getHeight());
    return SFML_coord;
}

sf::VertexArray compute_border(int window_length, int window_height){
    // Création d'un tableau de sommets pour les lignes
    sf::VertexArray lines(sf::Lines, 8);

    // Définir les coins
    sf::Vector2f top_left = sf::Vector2f(1, 0);
    sf::Vector2f top_right = sf::Vector2f(window_length, 0);
    sf::Vector2f bottom_right = sf::Vector2f(window_length, window_height-1);
    sf::Vector2f bottom_left = sf::Vector2f(1, window_height-1);

    lines[0].position = top_left;
    lines[0].color = sf::Color::Red;
    lines[1].position = top_right;
    lines[1].color = sf::Color::Red;

    lines[2].position = top_right;
    lines[2].color = sf::Color::Red;
    lines[3].position = bottom_right;
    lines[3].color = sf::Color::Red;

    lines[4].position = bottom_right;
    lines[4].color = sf::Color::Red;
    lines[5].position = bottom_left;
    lines[5].color = sf::Color::Red;

    lines[6].position = top_left;
    lines[6].color = sf::Color::Red;
    lines[7].position = bottom_left;
    lines[7].color = sf::Color::Red;

    return lines;
}

void display_universe_SFML(std::vector<std::vector<Coordinate>> particlesMovements, Box box, std::vector<double> particlesRadius, int scaleFactorPixels){

    // Set SFML dimensions proportional to Simulation dimensions
    int windowLength = scaleFactorPixels*box.getLength(); 
    int windowHeight = scaleFactorPixels*box.getHeight();

	// Create SFML windows
    sf::RenderWindow window(sf::VideoMode(windowLength, windowHeight), "Particle Movement", sf::Style::None);

    //Create borders
    sf::VertexArray borders = compute_border(windowLength, windowHeight);

    // Get numbers of particles
    int particle_numbers = particlesMovements.size();

    // Creating vector of SFML radius particles
    std::vector<double> SFML_particlesRadius;
    for (double& radius : particlesRadius){
        double SFML_radius = radius * scaleFactorPixels;
        SFML_particlesRadius.push_back(SFML_radius);
    }

    // Creation of SFML particles
    std::vector<sf::CircleShape> particles;
    for (int i = 0; i < particle_numbers; ++i) {
        sf::CircleShape particule;
        particule.setRadius(SFML_particlesRadius[i]);
        particule.setFillColor(sf::Color::White);
        particles.push_back(particule);
    }

    // index vector for following particles position 
    std::vector<std::size_t> indexes(particle_numbers, 0);

    // Set SFML Clock
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        for (int i=0;i<particle_numbers;i++){

            // particle index
            std::size_t &index = indexes[i];
            
            std::vector<Coordinate> coordinates = particlesMovements[i];
            // Mise à jour de la position de la particule en fonction du temps écoulé
            if (index < coordinates.size() && clock.getElapsedTime().asSeconds() >= coordinates[index].time) {
                std::array<double, 2> SFML_coord = coord_To_SFML_Coord(coordinates[index].x, coordinates[index].y, box, windowLength, windowHeight);
                particles[i].setPosition(SFML_coord[0]-SFML_particlesRadius[i], SFML_coord[1]-SFML_particlesRadius[i]);
                window.draw(particles[i]);
                index++;
            }
        }

        window.clear();
        for (sf::CircleShape particle : particles){window.draw(particle);}
        window.draw(borders);
        window.display();
    }
}