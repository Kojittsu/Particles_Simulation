#ifndef ARRAY_H
#define ARRAY_H

#include <array>

// Operators overloads declaration
std::array<double, 2> operator+(const std::array<double, 2>& lhs, const std::array<double, 2>& rhs);
std::array<double, 2> operator*(const std::array<double, 2>& lhs, const std::array<double, 2>& rhs);
std::array<double, 2> operator*(const std::array<double, 2>& lhs, double scalar);
std::array<double, 2> operator*(double scalar, const std::array<double, 2>& rhs);
std::array<double, 2>& operator+=(std::array<double, 2>& lhs, const std::array<double, 2>& rhs);

#endif