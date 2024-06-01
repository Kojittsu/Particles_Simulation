#include "box.h"

// Constructor
Box::Box(double xMin, double xMax, double yMin, double yMax) : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {}

// Default constructor
Box::Box() : xMin(0.0), xMax(0.0), yMin(0.0), yMax(0.0){}

// Getters
double Box::getXMIN() const {return xMin;}
double Box::getYMIN() const {return yMin;}
double Box::getXMAX() const {return xMax;}
double Box::getYMAX() const {return yMax;}

double Box::getLength() const{return xMax - xMin;}
double Box::getHeight() const{return yMax - yMin;}