#include "ShapeNode.h"
#include "Shape.h"
#include <iostream>
#include <string>

using namespace std;

ShapeNode::ShapeNode() {
    myShape = NULL;
    next = NULL;
}

// deletes the shape pointed to by myShape

ShapeNode::~ShapeNode() {
    delete myShape;
}

Shape* ShapeNode::getShape() const {
    return myShape;
}

void ShapeNode::setShape(Shape* ptr) {
    myShape = ptr;
}

ShapeNode* ShapeNode::getNext() const {
    return next;
}

void ShapeNode::setNext(ShapeNode* ptr) {
    next = ptr;
}

void ShapeNode::print() const {
    if (myShape != NULL) myShape->draw();
}

