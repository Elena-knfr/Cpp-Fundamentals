#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Shape.h"
#include "Rectangle.h"

// Build a rectangle object
Rectangle::Rectangle(string n, float xcent, float ycent, float w, float h):Shape(n, xcent, ycent) {
    width = w;
    height = h;
}

Rectangle::~Rectangle() {
    // Nothing to do
}

// accessors
float Rectangle::getWidth() const {
    return width;
}

float Rectangle::getHeight() const {
    return height;
}

// mutators
void Rectangle::setWidth(float w) {
    width = w;
}

void Rectangle::setHeight(float h) {
    height = h;
}

void Rectangle::draw() const {
    // Set floating point printing to fixed point with 2 decimals
    cout << std::fixed;
    cout << std::setprecision(2);
    
    // Print the information
    cout << "rectangle: " << name << " "
         << x_centre << " " << y_centre
         << " " << width << " " << height << " " << computeArea()
         << endl;
}

float Rectangle::computeArea() const {
    return (width*height);
}

Shape* Rectangle::clone() const {
    return (new Rectangle(*this));
}

