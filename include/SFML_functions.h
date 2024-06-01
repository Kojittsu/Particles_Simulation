#ifndef SFML_FUNCTIONS
#define SFML_FUNCTIONS

#include <array>
#include "box.h"

// Structure to store space and time coordinates
struct Coordinate {
    double time;
    double particle_number;
    double x;
    double y;

    Coordinate(double time, double x, double y) : time(time), x(x), y(y) {}
};

std::array<double, 2> coord_To_SFML_Coord(const double x, const double y, const Box &box, int window_length, int window_height);

sf::VertexArray compute_border(int window_length, int window_height);

void display_universe_SFML(std::vector<std::vector<Coordinate>> particleMovements, Box box, double radius, int window_length, int window_height);

#endif
