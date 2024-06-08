#include "array.h"

// Implementation of the + operator overload
std::array<double, 2> operator+(const std::array<double, 2>& lhs, const std::array<double, 2>& rhs) {
    return {lhs[0] + rhs[0], lhs[1] + rhs[1]};
}

// Implementation of the - operator overload
std::array<double, 2> operator-(const std::array<double, 2>& lhs, const std::array<double, 2>& rhs) {
    return {lhs[0] - rhs[0], lhs[1] - rhs[1]};
}

// Implementation of the * operator overload
std::array<double, 2> operator*(const std::array<double, 2>& lhs, const std::array<double, 2>& rhs) {
    return {lhs[0] * rhs[0], lhs[1] * rhs[1]};
}

// Implementation of the * operator overload for a right-hand scalar
std::array<double, 2> operator*(const std::array<double, 2>& lhs, double scalar) {
    return {lhs[0] * scalar, lhs[1] * scalar};
}

// Implementation of the * operator overload for a left-hand scalar
std::array<double, 2> operator*(double scalar, const std::array<double, 2>& rhs) {
    return {scalar * rhs[0], scalar * rhs[1]};
}

// Implementation of the += operator overload
std::array<double, 2>& operator+=(std::array<double, 2>& lhs, const std::array<double, 2>& rhs) {
    lhs[0] += rhs[0];
    lhs[1] += rhs[1];
    return lhs;
}

double getMagnitude(const std::array<double, 2> array) {
        return std::sqrt(array[0] * array[0] + array[1] * array[1]);
    }