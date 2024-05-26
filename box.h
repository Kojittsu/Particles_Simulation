#ifndef BOX_H
#define BOX_H

class Box {
public:
    // Constructor
    Box(double xMin, double xMax, double yMin, double yMax);
    
    // Getters
    double getXMIN() const;
    double getYMIN() const;
    double getXMAX() const;
    double getYMAX() const;

    double getLength() const;
    double getHeight() const;

private:
    double xMin;
    double xMax;
    double yMin;
    double yMax;
};

#endif
