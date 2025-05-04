#ifndef BOX_H
#define BOX_H

#include "array.h"

class Box {
public:
    // Constructor
    Box(const std::array<double, 3>& boxOrigin, double boxLength, double boxHeight, double boxDepth);

    std::array<double, 3> m_origin;
    double m_length;
    double m_height;
    double m_depth;
};

#endif