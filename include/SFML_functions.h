#ifndef SFML_FUNCTIONS
#define SFML_FUNCTIONS

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
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

sf::VertexArray computeBorder(int window_length, int window_height);

std::vector<std::vector<Coordinate>> readParticlesMovements(const std::string& filename);

void display_universe_SFML(std::vector<std::vector<Coordinate>> particleMovements, Box box, std::vector<double> particlesRadius, int scaleFactorPixels);

#endif
