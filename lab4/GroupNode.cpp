#include "GroupNode.h"
#include "ShapeList.h"
#include "ShapeNode.h"
#include "Shape.h"
#include <iostream>
#include <string>

using namespace std;


// sets group name to n and makes myShapeList
// point to a new ShapeList; sets next to nullptr

GroupNode::GroupNode(string n) {
    name = n;
    myShapeList = new ShapeList();
    next = NULL;
}

// deletes the myShapeList list

GroupNode::~GroupNode() {
    delete myShapeList;
}

//returns group name

string GroupNode::getName() const {
    return name;
}

//returns myShapeList

ShapeList* GroupNode::getShapeList() const {
    return myShapeList;
}

//sets myShapeList to ptr

void GroupNode::setShapeList(ShapeList* ptr) {
    myShapeList = ptr;
}

//returns next

GroupNode* GroupNode::getNext() const {
    return next;
}

//sets next to ptr

void GroupNode::setNext(GroupNode* ptr) {
    next = ptr;
}

// prints the GroupNode  

void GroupNode::print() const {
    cout << name << ":" << endl;
    myShapeList->print();
}


