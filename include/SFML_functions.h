#ifndef SFML_FUNCTIONS
#define SFML_FUNCTIONS

#include <array>
#include "box.h"

std::array<double, 2> coord_To_SFML_Coord(const double x, const double y, const Box &box, int window_length, int window_height);

sf::VertexArray compute_border(int window_length, int window_height);

#endif
