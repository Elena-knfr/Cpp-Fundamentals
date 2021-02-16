#ifndef Rectangle_h
#define Rectangle_h

#include <iostream>
#include <string>
using namespace std;

#include "Shape.h"

// This class implements the rectangle Shape objects.

class Rectangle : Shape {
private:
    float width;
    float height;
public:
    //constructor
    Rectangle(string n, float xcen, float ycen, float w, float h);
    
    //destructor
    virtual ~Rectangle();
    
    //accessors
    float getWidth() const; // returns width of the rectangle
    float getHeight() const; //returns height of the rectangle
    
    //mutators
    void setWidth(float w); //sets width of the rectangle
    void setHeight(float h); //sets height of the rectangle
    
    //utility methods
    virtual void draw() const; //draw the rectangle
    
    virtual float computeArea() const;   // Computes the area of the rectangle
    
    virtual Shape* clone() const;  // Clones the object
};

#endif /* Rectangle_h */


