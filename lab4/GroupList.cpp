#include <iostream>
#include <string>
#include "GroupNode.h"
#include "GroupList.h"
#include "Shape.h"
#include "ShapeList.h"
#include "ShapeNode.h"

using namespace std;

// sets head to nullptr

GroupList::GroupList() {
    head = NULL;
}

// deletes all list nodes, including all the ShapeList
// attached to each GroupNode

GroupList::~GroupList() {
}

// returns the head pointer

GroupNode* GroupList::getHead() const {
    return head;
}

// sets the head pointer to ptr

void GroupList::setHead(GroupNode* ptr) {
    head = ptr;
}

// inserts the node pointed to by s at the end of the list

void GroupList::insert(GroupNode* s) {
    if (head == NULL) {
        head = s;
        s->setNext(NULL);
    } else {
        GroupNode* tptr = head;
        while (tptr->getNext() != NULL) {
            tptr = tptr->getNext();
        }
        tptr->setNext(s);
        s->setNext(NULL);
    }
}

// removes the group with the name "name" from the list
// and returns a pointer to the removed GroupNode 
// returns nullptr is name is not found on list 

GroupNode* GroupList::remove(string name) {
    if (head == NULL) return NULL;
    GroupNode* tptr = head;
    GroupNode* pptr = NULL;
    while (tptr != NULL) {
        if (tptr->getName() == name) break;
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

// prints the list, one GroupNode at a time

void GroupList::print() const {
    GroupNode* pptr = head;
    while (pptr != NULL) {
        pptr->print();
        pptr = pptr->getNext();
    }
}




