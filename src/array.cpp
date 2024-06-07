// src/array.cpp

#include "array.h"

// Implémentation de la surcharge de l'opérateur +
std::array<double, 2> operator+(const std::array<double, 2>& lhs, const std::array<double, 2>& rhs) {
    return {lhs[0] + rhs[0], lhs[1] + rhs[1]};
}

// Implémentation de la surcharge de l'opérateur *
std::array<double, 2> operator*(const std::array<double, 2>& lhs, const std::array<double, 2>& rhs) {
    return {lhs[0] * rhs[0], lhs[1] * rhs[1]};
}

// Implémentation de la surcharge de l'opérateur * pour un scalaire à droite
std::array<double, 2> operator*(const std::array<double, 2>& lhs, double scalar) {
    return {lhs[0] * scalar, lhs[1] * scalar};
}

// Implémentation de la surcharge de l'opérateur * pour un scalaire à gauche
std::array<double, 2> operator*(double scalar, const std::array<double, 2>& rhs) {
    return {scalar * rhs[0], scalar * rhs[1]};
}

// Implémentation de la surcharge de l'opérateur +=
std::array<double, 2>& operator+=(std::array<double, 2>& lhs, const std::array<double, 2>& rhs) {
    lhs[0] += rhs[0];
    lhs[1] += rhs[1];
    return lhs;
}
