#ifndef Triangle_h
#define Triangle_h

#include <iostream>
#include <string>
#include "Shape.h"
using namespace std;


// This class implements the triangle Shape objects.

class Triangle : Shape {
private:
    float xVertice1;                  
    float yVertice1;
    float xVertice2;
    float yVertice2;
    float xVertice3;
    float yVertice3;
public:
    // Constructor
    Triangle(string n, float x_vertice1, float y_vertice1, float x_vertice2, float y_vertice2, float x_vertice3, float y_vertice3);
    
    // Destructor
    virtual ~Triangle();
    
    // Accessors
    float getxVertice1() const; 
    float getyVertice1() const; 
    float getxVertice2() const; 
    float getyVertice2() const; 
    float getxVertice3() const; 
    float getyVertice3() const; 
    
    // Mutators
    void setxVertice1(float x_vertice1); 
    void setyVertice1(float y_vertice1); 
    void setxVertice2(float x_vertice2); 
    void setyVertice2(float y_vertice2); 
    void setxVertice3(float x_vertice3); 
    void setyVertice3(float y_vertice3); 
    
    // Utility methods
    virtual void draw() const;     
    
    virtual float computeArea() const;   // Computes the area 
    
    virtual Shape* clone() const;  // Clones the object
};


#endif /* Triangle_h */


