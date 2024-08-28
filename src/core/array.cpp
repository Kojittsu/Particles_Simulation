#include "array.h"

// Implementation of the + operator overload
std::array<double, 3> operator+(const std::array<double, 3>& lhs, const std::array<double, 3>& rhs) {
    return {lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]};
}

// Implementation of the - operator overload
std::array<double, 3> operator-(const std::array<double, 3>& lhs, const std::array<double, 3>& rhs) {
    return {lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]};
}

// Implementation of the * operator overload
std::array<double, 3> operator*(const std::array<double, 3>& lhs, const std::array<double, 3>& rhs) {
    return {lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]};
}

// Implementation of the * operator overload for a right-hand scalar
std::array<double, 3> operator*(const std::array<double, 3>& lhs, double scalar) {
    return {lhs[0] * scalar, lhs[1] * scalar, lhs[2] * scalar};
}

// Implementation of the * operator overload for a left-hand scalar
std::array<double, 3> operator*(double scalar, const std::array<double, 3>& rhs) {
    return {scalar * rhs[0], scalar * rhs[1], scalar * rhs[2]};
}

// Implementation of the += operator overload
std::array<double, 3>& operator+=(std::array<double, 3>& lhs, const std::array<double, 3>& rhs) {
    lhs[0] += rhs[0];
    lhs[1] += rhs[1];
    lhs[2] += rhs[2];
    return lhs;
}

double getMagnitude(const std::array<double, 3> array) {
        return std::sqrt(array[0] * array[0] + array[1] * array[1] + array[2] * array[2]);
    }

// Implementation of the scalar product function
double dotProduct(const std::array<double, 3>& lhs, const std::array<double, 3>& rhs) {
    return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}