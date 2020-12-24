#include "ShapeList.h"
#include "ShapeNode.h"
#include "Shape.h"
#include <iostream>
#include <string>

using namespace std;

//sets head to nullptr

ShapeList::ShapeList() {
    head = NULL;
}

//deletes all list nodes starting with head plus associated shapes

ShapeList::~ShapeList() {
}

ShapeNode* ShapeList::getHead() const {
    return head;
}

void ShapeList::setHead(ShapeNode* ptr) {
    head = ptr;
}

// finds a shape node with the specified shape name
// returns a pointer to the node if found, otherwise
// returns nullptr if the node is not found

ShapeNode* ShapeList::find(string name) const {
    ShapeNode* tptr = head;
    while (tptr != NULL) {
        if (tptr->getShape()->getName() == name) return tptr;
        tptr = tptr->getNext();
    }
    return NULL;
}

// inserts the node pointed to by s at the end
// of the list; s should never be nullptr

void ShapeList::insert(ShapeNode* s) {
    if (head == NULL) {
        head = s;
        s->setNext(NULL);
    } else {
        ShapeNode* tptr = head;
        while (tptr->getNext() != NULL) {
            tptr = tptr->getNext();
        }
        tptr->setNext(s);
        s->setNext(NULL);
    }
}

// removes the node with the shape called name
// returns a pointer to the removed node or 
// nullptr is a node with name does not exist 

ShapeNode* ShapeList::remove(string name) {
    if (head == NULL) return NULL;
    ShapeNode* tptr = head;
    ShapeNode* pptr = NULL;
    while (tptr != NULL) {
        if (tptr->getShape()->getName() == name) break;
        pptr = tptr;
        tptr = tptr->getNext();
    }
    if (tptr == NULL) return NULL;
    if (tptr == head) {
        head = head->getNext();
        return tptr;
    }
    pptr->setNext(tptr->getNext());
    return tptr;
}

// prints the list

void ShapeList::print() const {
    ShapeNode* tptr = head;
    while (tptr != NULL) {
        tptr->print();
        tptr = tptr->getNext();
    }
}
