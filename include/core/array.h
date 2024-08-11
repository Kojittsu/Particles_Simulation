#ifndef ARRAY_H
#define ARRAY_H

#include <array>
#include <cmath>

// Operators overloads declaration
std::array<double, 2> operator+(const std::array<double, 2>& lhs, const std::array<double, 2>& rhs);
std::array<double, 2> operator-(const std::array<double, 2>& lhs, const std::array<double, 2>& rhs);
std::array<double, 2> operator*(const std::array<double, 2>& lhs, const std::array<double, 2>& rhs);
std::array<double, 2> operator*(const std::array<double, 2>& lhs, double scalar);
std::array<double, 2> operator*(double scalar, const std::array<double, 2>& rhs);
std::array<double, 2>& operator+=(std::array<double, 2>& lhs, const std::array<double, 2>& rhs);

double getMagnitude(const std::array<double, 2> array);
double dotProduct(const std::array<double, 2>& lhs, const std::array<double, 2>& rhs);

#endif