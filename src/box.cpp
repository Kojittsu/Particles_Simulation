#include "box.h"

// Constructor
Box::Box(const std::array<double, 3>& boxOrigin, double boxLength, double boxHeight, double boxDepth)
    : m_origin(boxOrigin), m_length(boxLength), m_height(boxHeight), m_depth(boxDepth) {}