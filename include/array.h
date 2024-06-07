// include/array.h

#ifndef ARRAY_H
#define ARRAY_H

#include <array>

// Déclaration de la surcharge de l'opérateur +
std::array<double, 2> operator+(const std::array<double, 2>& lhs, const std::array<double, 2>& rhs);

// Déclaration de la surcharge de l'opérateur *
std::array<double, 2> operator*(const std::array<double, 2>& lhs, const std::array<double, 2>& rhs);

// Déclaration de la surcharge de l'opérateur *
std::array<double, 2> operator*(const std::array<double, 2>& lhs, double scalar);
std::array<double, 2> operator*(double scalar, const std::array<double, 2>& rhs);

// Déclaration de la surcharge de l'opérateur +=
std::array<double, 2>& operator+=(std::array<double, 2>& lhs, const std::array<double, 2>& rhs);

#endif // ARRAY_H
