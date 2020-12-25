#ifndef Circle_h
#define Circle_h

#include <iostream>
#include <string>
using namespace std;

#define PI 3.1415926               // Historically, this is a useful constant

// This class implements the circle Shape objects.
// It inherits from the base Shape class and extends it
// to add the radius as well as implement the abstract
// methods of Shape. Use it as a template to implement
// the other shapes required in the assignment.

// ***********  ECE244 Student: DO NOT MODIFY THIS FILE  ***********


#include "Shape.h"

class Circle : Shape {
private:
    float radius;                  // The radius of the circle

public:
    // Constructor
    Circle (string n, float xcent, float ycent, float r);
    
    // Destructor
    virtual ~Circle();
    
    // Accessor
    float getRadius() const;       // Returns the radius of the circle

    // Mutator
    void setRadius(float r);       // Sets the radius of the circle
    
    // Utility methods
    virtual void draw() const;     // Draws thye circle; for the assignment it
                                   // prints the information of the circle
    
    virtual float computeArea() const;   // Computes the area of the circle
    
    virtual Shape* clone() const;  // Clones the object
};

#endif /* Circle_h */


