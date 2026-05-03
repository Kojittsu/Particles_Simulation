#include "box.h"

// Constructor
Box::Box(const std::array<double, 3>& origin, const double length, const double height, const double depth)
    : origin_(origin), length_(length), height_(height), depth_(depth)
    {
        // Validate the parameters
        if (length <= 0) {
            throw std::invalid_argument("Box length must be > 0");
        }
        if (height <= 0) {
            throw std::invalid_argument("Box height must be > 0");
        }
        if (depth <= 0) {
            throw std::invalid_argument("Box depth must be > 0");
        }
    }
