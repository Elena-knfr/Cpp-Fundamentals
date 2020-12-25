#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

// Build an object
Triangle::Triangle(string n, float x_vertice1, float y_vertice1, float x_vertice2, float y_vertice2, float x_vertice3, 
        float y_vertice3):Shape(n, (x_vertice1 +  x_vertice2 +  x_vertice3) / 3.00, (y_vertice1 +  y_vertice2 +  y_vertice3) / 3.00) {
    xVertice1 = x_vertice1;                  
    yVertice1 = y_vertice1;
    xVertice2 = x_vertice2;
    yVertice2 = y_vertice2;
    xVertice3 = x_vertice3;
    yVertice3 = y_vertice3;
}

Triangle::~Triangle() {
    // Nothing to do
}

// accessors
float Triangle::getxVertice1() const {
    return xVertice1;
} 

float Triangle::getyVertice1() const {
    return yVertice1;
} 

float Triangle::getxVertice2() const {
    return xVertice2;
}

float Triangle::getyVertice2() const {
    return yVertice2;
}

float Triangle::getxVertice3() const {
    return xVertice3;
}

float Triangle::getyVertice3() const {
    return yVertice3;
}

// mutators
void Triangle::setxVertice1(float x_vertice1){
    xVertice1 = x_vertice1;
} 

void Triangle::setyVertice1(float y_vertice1){
    yVertice1 = y_vertice1;
}

void Triangle::setxVertice2(float x_vertice2){
    xVertice2 = x_vertice2;
}

void Triangle::setyVertice2(float y_vertice2){
    yVertice2 = y_vertice2;
}

void Triangle::setxVertice3(float x_vertice3){
    xVertice3 = x_vertice3;
}

void Triangle::setyVertice3(float y_vertice3){
    yVertice3 = y_vertice3;
}


void Triangle::draw() const {
    // Set floating point printing to fixed point with 2 decimals
    cout << std::fixed;
    cout << std::setprecision(2);
    
    // Print the information
    cout << "triangle: " << name << " "
         << x_centre << " " << y_centre
         << " " << xVertice1 << " " << yVertice1 
         << " " << xVertice2 << " " << yVertice2 << " "
         << xVertice3 << " " << yVertice3 << " " << computeArea()
         << endl;
}

float Triangle::computeArea() const {
    float TriArea = (xVertice1*(yVertice2-yVertice3) + xVertice2*(yVertice3-yVertice1) + xVertice3*(yVertice1-yVertice2))/2.00;
    if (TriArea < 0) TriArea = -TriArea;
    return TriArea;
}

Shape* Triangle::clone() const {
    return (new Triangle(*this));
}



















