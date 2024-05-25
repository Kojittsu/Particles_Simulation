#include "box.h"

// Constructor
Box::Box(double xMin, double xMax, double yMin, double yMax) : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {}

// Getters
double Box::getXMIN() const {return xMin;}
double Box::getYMIN() const {return yMin;}
double Box::getXMAX() const {return xMax;}
double Box::getYMAX() const {return yMax;}