#ifndef BOX_H
#define BOX_H

#include <stdexcept>
#include "array.h"

class Box {
public:
    Box(const std::array<double, 3>& origin, const double length, const double height, const double depth);

    const std::array<double, 3> origin_;
    const double length_;
    const double height_;
    const double depth_;
};

#endif
