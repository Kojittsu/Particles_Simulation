#ifndef SFML_FUNCTIONS
#define SFML_FUNCTIONS

#include <array>
#include "box.h"

// Structure to store space and time coordinates
struct Coordinate {
    double time;
    double x;
    double y;
};

std::array<double, 2> coord_To_SFML_Coord(const double x, const double y, const Box &box, int window_length, int window_height);

sf::VertexArray compute_border(int window_length, int window_height);

void display_universe_SFML(std::vector<Coordinate> coordinates, Box box, double radius, int window_length, int window_height);

#endif
