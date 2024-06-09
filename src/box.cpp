#include "box.h"

// Constructor
Box::Box(double xOrigin, double yOrigin, double length, double height) : xOrigin(xOrigin), yOrigin(yOrigin), length(length), height(height) {}

// Default constructor
Box::Box() : xOrigin(0.0), yOrigin(0.0), length(0.0), height(0.0){}

// Getters
double Box::getXOrigin() const {return xOrigin;}
double Box::getYOrigin() const {return yOrigin;}
double Box::getLength() const{return length;}
double Box::getHeight() const{return height;}

double Box::getXMAX() const {return xOrigin + length;}
double Box::getYMAX() const {return yOrigin + height;}