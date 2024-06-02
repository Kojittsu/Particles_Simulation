#ifndef CIRCLE_H
#define CIRCLE_H

class Circle {
public:
    // Constructor
    Circle(double centerX, double centerY, double radius);

    // Default constructor
    Circle();

    // Getters
    double getCenterX() const;
    double getCenterY() const;
    double getRadius() const;

private:
    double centerX, centerY, radius;
};

#endif // CIRCLE_H