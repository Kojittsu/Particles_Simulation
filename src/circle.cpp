#include "circle.h"

// Constructor
Circle::Circle(double centerX, double centerY, double radius) : centerX(centerX), centerY(centerY), radius(radius) {}

// Default constructor
Circle::Circle() : centerX(0.0), centerY(0.0), radius(0.0){}

// Getters
double Circle::getCenterX() const{return centerX;}
double Circle::getCenterY() const{return centerY;}
double Circle::getRadius() const{return radius;}