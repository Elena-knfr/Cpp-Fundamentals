#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itself must be allocated
GroupList* gList;

//store the previous number of maxShapes to be able to deallocate the allocated memory when entering new maxShape command
int prev_count = -1;

void shape(stringstream & line);
void group(stringstream & line);
void move(stringstream & line);
void draw(stringstream & line);
void delete_(stringstream & line);

void invalidCommand();
void invalidName();
void nameExists(string s);
void shapeNameNotFound(string h);
void groupNameNotFound(string k);

bool name_validity(string name);
bool shape_existance(string shape_name);
bool group_existance(string group_name);

int main() {
    // Create the groups list
    gList = new GroupList();

    // Create the pool group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS - 1]);
    gList->insert(poolGroup);

    string line;
    string command;

    cout << "> "; // Prompt for input
    getline(cin, line); // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream(line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly

        //shape
        if (command == keyWordsList[0]) {
            shape(lineStream);
        }//group
        else if (command == keyWordsList[1]) {
            group(lineStream);
        }//move
        else if (command == keyWordsList[2]) {
            move(lineStream);
        }//delete
        else if (command == keyWordsList[3]) {
            delete_(lineStream);
        }//draw
        else if (command == keyWordsList[4]) {
            draw(lineStream);
        } else {
            invalidCommand();
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> "; // Prompt for input
        getline(cin, line);

    } // End input loop until EOF.
    return 0;
}

void shape(stringstream & line) {
    string shapeName, shapeType;
    int locationX, locationY, sizeX, sizeY;
    bool validKey = true;

    line >> shapeName;

    if (name_validity(shapeName) == false) {
        invalidName();
        validKey = false;
    } else if ((shape_existance(shapeName) == true) || (group_existance(shapeName) == true)) {
        nameExists(shapeName);
        validKey = false;
    }
    else {
        line >> shapeType;
        line >> locationX;
        line >> locationY;
        line >> sizeX;
        line >> sizeY;
    }

    if (validKey == true) {
        Shape* ptr = new Shape(shapeName, shapeType, locationX, sizeX, locationY, sizeY);
        ShapeNode* node = new ShapeNode();
        gList->getHead()->getShapeList()->insert(node);
        node->setShape(ptr);
        cout << shapeName << ": " << shapeType << " " << locationX << " " <<
                locationY << " " << sizeX << " " << sizeY << endl;
    }
}

void group(stringstream & line) {
    string groupName;
    bool validKey = true;

    line >> groupName;

    if (name_validity(groupName) == false) {
        invalidName();
        validKey = false;
    } else if ((group_existance(groupName) == true) || (shape_existance(groupName) == true)) {
        nameExists(groupName);
        validKey = false;
    }

    if (validKey == true) {
        GroupNode* node = new GroupNode(groupName);
        gList->insert(node);
        cout << groupName << ": " << "group" << endl;
    }
}

void move(stringstream & line) {
    string shapeName, groupName;
    bool shapeExists, groupExists;
    bool validKey = true;

    line >> shapeName;
    shapeExists = shape_existance(shapeName);
    line >> groupName;
    groupExists = group_existance(groupName);

    if ((name_validity(shapeName) == false) || (name_validity(groupName) == false)) {
        invalidName();
        validKey = false;
    } else if (shapeExists != true) {
        shapeNameNotFound(shapeName);
        validKey = false;
    } else if (groupExists != true) {
        groupNameNotFound(groupName);
        validKey = false;
    }

    if (validKey == true) {
        GroupNode* kptr = gList->getHead();
        while (kptr != NULL) {
            if (kptr->getName() == groupName) break;
            kptr = kptr->getNext();
        }
        GroupNode* pptr = gList->getHead();
        while (pptr != NULL) {
            ShapeNode* ptr = pptr->getShapeList()->find(shapeName);
            if (ptr == NULL) {
                pptr = pptr->getNext();
            } else {
                ShapeNode* kpr = pptr->getShapeList()->remove(shapeName);
                //insert kpr to the group we want
                kptr->getShapeList()->insert(kpr);
                break;

            }
        }
        cout << "moved " << shapeName << " to " << groupName << endl;
    }
}

void draw(stringstream & line) {
    cout << "drawing:" << endl;
    gList->print();
}

void delete_(stringstream & line) {
    string name;
    bool shapeExists, groupExists;
    //bool validKey = true;

    line >> name;
    shapeExists = shape_existance(name);
    groupExists = group_existance(name);
    if (name_validity(name) == false) {
        invalidName();
        //validKey = false;
    } else if (groupExists != true) {
        if (shapeExists != true) {
            shapeNameNotFound(name);
        } else {
            GroupNode* pptr = gList->getHead();
            while (pptr != NULL) {
                ShapeNode* tpr = pptr->getShapeList()->getHead();
                ShapeNode* kpr = NULL;
                while (tpr != NULL) {
                    if (tpr->getShape()->getName() == name) {
               
                        if (kpr == NULL) {
                            pptr->getShapeList()->setHead(tpr->getNext());
                        }
                        else {
                            kpr->setNext(tpr->getNext());
                        }
                        delete tpr;
                        cout << name << ": deleted" << endl;
                        break;
                        
                    }
                    kpr = tpr;
                    tpr = tpr->getNext();
                }
                pptr = pptr->getNext();
            }
        }
    } else {
        GroupNode* ttpr = gList->getHead();
        GroupNode* kkpr = NULL;
        ShapeNode* node = gList->getHead()->getShapeList()->getHead();
        while (ttpr != NULL) {
            if (ttpr->getName() == name) {
                if (node == NULL){
                    gList->getHead()->getShapeList()->setHead(ttpr->getShapeList()->getHead());
                }
                else {
                    while (node->getNext() != NULL){
                        node = node->getNext();
                    }
                    node->setNext(ttpr->getShapeList()->getHead());
                }
                kkpr->setNext(ttpr->getNext());
                delete ttpr;
                cout << name << ": deleted" << endl;
                break;
            }
            kkpr = ttpr;
            ttpr = ttpr->getNext();
        }
    }
}

void invalidCommand() {
    cout << "error: invalid command" << endl;
}

void invalidName() {
    cout << "error: invalid name" << endl;
}

void nameExists(string s) {
    cout << "error: name " << s << " exists" << endl;
}

void shapeNameNotFound(string h) {
    cout << "error: shape " << h << " not found" << endl;
}

void groupNameNotFound(string k) {
    cout << "error: group " << k << " not found" << endl;
}

//check the shape name to be not one of the commands or shape type
bool name_validity(string name) {
    for (int i = 0; i < 6; ++i) {
        if (name == keyWordsList[i]) {
            return false;
        }
    }
    for (int i = 0; i < 3; ++i) {
        if (name == shapeTypesList[i]) {
            return false;
        }
    }
    return true;
}

bool shape_existance(string shapeName) {
    GroupNode* pptr = gList->getHead();
    while (pptr != NULL) {
        ShapeNode* tpr = pptr->getShapeList()->getHead();
        while (tpr != NULL) {
            if (tpr->getShape()->getName() == shapeName) {
                return true;
            }
            tpr = tpr->getNext();
        }
        pptr = pptr->getNext();
    }
}

bool group_existance(string groupName) {
    GroupNode* tpr = gList->getHead();
    while (tpr != NULL) {
        if (tpr->getName() == groupName) {
            return true;
        }
        tpr = tpr->getNext();
    }
}

