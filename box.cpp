#include "box.h"

// Constructor
Box::Box(double xMin, double xMax, double yMin, double yMax) : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {}

// Default constructor
Box::Box() {}

// Getters
double Box::getXMIN() const {return xMin;}
double Box::getYMIN() const {return yMin;}
double Box::getXMAX() const {return xMax;}
double Box::getYMAX() const {return yMax;}

double Box::getLength() const{return xMax - xMin;}
double Box::getHeight() const{return yMax - yMin;}