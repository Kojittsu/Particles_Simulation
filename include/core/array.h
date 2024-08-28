#ifndef ARRAY_H
#define ARRAY_H

#include <array>
#include <cmath>

// Operators overloads declaration
std::array<double, 3> operator+(const std::array<double, 3>& lhs, const std::array<double, 3>& rhs);
std::array<double, 3> operator-(const std::array<double, 3>& lhs, const std::array<double, 3>& rhs);
std::array<double, 3> operator*(const std::array<double, 3>& lhs, const std::array<double, 3>& rhs);
std::array<double, 3> operator*(const std::array<double, 3>& lhs, double scalar);
std::array<double, 3> operator*(double scalar, const std::array<double, 3>& rhs);
std::array<double, 3>& operator+=(std::array<double, 3>& lhs, const std::array<double, 3>& rhs);

double getMagnitude(const std::array<double, 3> array);
double dotProduct(const std::array<double, 3>& lhs, const std::array<double, 3>& rhs);

#endif