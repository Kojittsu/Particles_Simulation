#ifndef SFML_FUNCTIONS
#define SFML_FUNCTIONS

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdint>
#include "box.h"
#include "circle.h"

// Structure to store space and time coordinates
struct Coordinate {
    double time;
    double particle_number;
    double x;
    double y;

    Coordinate(double time, double x, double y) : time(time), x(x), y(y) {}
};

std::array<double, 2> Calculate_SFML_Coord(const double x, const double y, const Box &box, double scaleFactorPixels);

sf::VertexArray computeBorder(int window_length, int window_height);

sf::VertexArray computeCircle(double centerX, double centerY, int radius, int pointCount);

std::vector<std::vector<Coordinate>> readParticleMovements(const std::string& filename);

void RenderParticleMovements(std::vector<std::vector<Coordinate>> particleMovements, Box box, Circle circle, std::vector<double> particlesRadius, double scaleFactorPixels);

#endif
