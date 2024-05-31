#include <SFML/Graphics.hpp>
#include "SFML_functions.h"

std::array<double, 2> coord_To_SFML_Coord(const double x, const double y, const Box &box, int window_length, int window_height){
    std::array<double, 2> SFML_coord;
    SFML_coord[0] = x * window_length / box.getLength();
    SFML_coord[1] = window_height - (y * window_height / box.getHeight());
    // std::cout << "Coord: x=" << x << ", y=" << y << " | SFML_Coord: x=" << SFML_coord[0] << ", y=" << SFML_coord[1] << "\n";
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