#ifndef BOX_H
#define BOX_H

class Box {
public:
    // Constructor
    Box(double xOrigin, double yOrigin, double length, double height);

    // Default constructor
    Box();
    
    // Getters
    double getXOrigin() const;
    double getYOrigin() const;
    double getLength() const;
    double getHeight() const;

    double getXMAX() const;
    double getYMAX() const;

private:
    double xOrigin;
    double yOrigin;
    double length;
    double height;
};

#endif
