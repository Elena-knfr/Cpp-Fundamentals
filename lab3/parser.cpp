//
//  parser.cpp
//  lab3
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

//store the previous number of maxShapes to be able to deallocate the allocated memory when entering new maxShape command
int prev_count = -1;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
void maxShapes(stringstream & line);
void create(stringstream & line);
void move(stringstream & line);
void rotate(stringstream & line);
void draw(stringstream & line);
void delete_(stringstream & line);

void invalidCommand();
void invalidArg();
void invalidName();
void nameExists(string shapeN);
void nameNotFound(string shapeN);
void invalidType();
void invalidValue();
void manyArgs();
void fewArgs();
void full();

bool shapeName_validity(string shape_name);
bool shapeName_existance(string shape_name);
bool shapeType_validity(string shape_type);
bool validVal(int loc);
int shape_location(string shape_name);
bool validRotation(int ang);

int main() {

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
        // ECE244 Student: Insert your code here

        //maxShapes
        if (command == keyWordsList[1]) {
            maxShapes(lineStream);
        }//create
        else if (command == keyWordsList[2]) {
            create(lineStream);
        }//move
        else if (command == keyWordsList[3]) {
            move(lineStream);
        }//rotate
        else if (command == keyWordsList[4]) {
            rotate(lineStream);
        }//draw
        else if (command == keyWordsList[5]) {
            draw(lineStream);
        }//delete
        else if (command == keyWordsList[6]) {
            delete_(lineStream);
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

void maxShapes(stringstream & line) {
    bool validKeyword = true;
    
    line >> max_shapes;
    if (line.fail() || max_shapes < 0) {
        if (line.eof()) {
            validKeyword = false;
            //cout << validKeyword << endl;
            line.clear();
        } else {
            invalidValue();
            line.clear();
            line.ignore(10000, '\n');
        }
    } else {
        if (prev_count == -1) {
            prev_count = max_shapes;
            shapesArray = new Shape*[max_shapes];
            
            //initializing each element to NULL
            for (int i = 0; i < max_shapes; ++i) {
                shapesArray[i] = NULL;
            }
            cout << "New database: max shapes is " << max_shapes << endl;
        } else {
            shapeCount = 0;
            for (int i = 0; i < prev_count; ++i) {
                if (shapesArray[i] != NULL) {
                    delete shapesArray[i];
                    shapesArray[i] = NULL;
                }
            }
            delete [] shapesArray;
            shapesArray = NULL;
            prev_count = max_shapes;
            shapesArray = new Shape*[max_shapes];
            //initializing each element to NULL
            for (int i = 0; i < max_shapes; ++i) {
                shapesArray[i] = NULL;
            }
            cout << "New database: max shapes is " << max_shapes << endl;
        }
    }
}

void create(stringstream & line) {
    string shapeName, shapeType;
    int locationX, locationY, sizeX, sizeY;
    bool validKey = true;

    line >> shapeName;

    if (line.fail()) {
        fewArgs();
        validKey = false;
    } else if (shapeName_validity(shapeName) == false) {
        invalidName();
        validKey = false;
    } else if (shapeName_existance(shapeName) == false) {
        nameExists(shapeName);
        validKey = false;
    }
    else {
        line >> shapeType;

        if (line.fail()) {
            fewArgs();
            validKey = false;
        } else if (shapeType_validity(shapeType) == false) {
            invalidType();
            validKey = false;
        }
        else {

            line >> locationX;
            if (line.fail()) {
                if (line.eof()) {
                    fewArgs();
                    validKey = false;
                } else {
                    invalidArg();
                    validKey = false;
                }
            } else if (validVal(locationX) == false) {
                invalidValue();
                validKey = false;
            }
            else {

                line >> locationY;
                if (line.fail()) {
                    if (line.eof()) {
                        fewArgs();
                        validKey = false;
                    } else {
                        invalidArg();
                        validKey = false;
                    }
                } else if (validVal(locationY) == false) {
                    invalidValue();
                    validKey = false;
                }
                else {

                    line >> sizeX;
                    if (line.fail()) {
                        if (line.eof()) {
                            fewArgs();
                            validKey = false;
                        } else {
                            invalidArg();
                            validKey = false;
                        }
                    } else if (validVal(sizeX) == false) {
                        invalidValue();
                        validKey = false;
                    }
                    else {

                        line >> sizeY;
                        if (line.fail()) {
                            if (line.eof()) {
                                fewArgs();
                                validKey = false;
                            } else {
                                invalidArg();
                                validKey = false;
                            }
                        } else if (validVal(sizeY) == false) {
                            invalidValue();
                            validKey = false;
                        }
                        else if (shapeType == shapeTypesList[0]) {
                            if (sizeX != sizeY) {
                                invalidValue();
                                validKey = false;
                            } else if (shapeCount >= max_shapes) {
                                //cout << "shape count is: " << shapeCount << " and " << "max shape is: " << max_shapes << endl;
                                full();
                                validKey = false;
                            } else {
                                string more_argument;
                                line >> more_argument;
                                
                                if (!line.fail()) {
                                    manyArgs();
                                    validKey = false;
                                }
                            }
                        }//check the array if it is full or not
                        else if (shapeCount >= max_shapes) {
                            //cout << "shape count is: " << shapeCount << " and " << "max shape is: " << max_shapes << endl;
                            full();
                            validKey = false;
                        } else {
                            string more_arg;

                            line >> more_arg;
                            
                            if (!line.fail()) {
                                manyArgs();
                                validKey = false;
                            }
                        }
                    }
                }
            }
        }
    }

    if (validKey == true) {
        shapesArray[shapeCount] = new Shape(shapeName, shapeType, locationX, sizeX, locationY, sizeY);
        
        cout << "Created " << shapesArray[shapeCount]->getName() << ": "
                << shapesArray[shapeCount]->getType() << " " << shapesArray[shapeCount]->getXlocation() << " "
                << shapesArray[shapeCount]->getYlocation() << " " << shapesArray[shapeCount]->getXsize() << " "
                << shapesArray[shapeCount]->getYsize() << endl;

        shapeCount++;
       
    }
}

void move(stringstream & line) {
    string shapeMove;
    int locationXMove, locationYMove, location;
    bool validKey = true;

    line >> shapeMove;
    location = shape_location(shapeMove);

    if (line.fail()) {
        fewArgs();
        validKey = false;
    } else if (shapeName_validity(shapeMove) == false) {
        invalidName();
        validKey = false;
    } else if (location == -1) {
        nameNotFound(shapeMove);
        validKey = false;
    } else {
        line >> locationXMove;
        if (line.fail()) {
            if (line.eof()) {
                fewArgs();
                validKey = false;
            } else {
                invalidArg();
                validKey = false;
            }
        } else if (validVal(locationXMove) == false) {
            invalidValue();
            validKey = false;
        } else {

            line >> locationYMove;
            if (line.fail()) {
                if (line.eof()) {
                    fewArgs();
                    validKey = false;
                } else {
                    invalidArg();
                    validKey = false;
                }
            } else if (validVal(locationYMove) == false) {
                invalidValue();
                validKey = false;
            } else {

                string more_arg;
                line >> more_arg;
                if (!line.fail()) {
                    manyArgs();
                    validKey = false;
                }

            }
        }
    }

    if (validKey == true) {
        shapesArray[location]->setXlocation(locationXMove);
        shapesArray[location]->setYlocation(locationYMove);
        cout << "Moved " << shapeMove << " to " << locationXMove << " "
                << locationYMove << endl;
    }
}

void rotate(stringstream & line) {
    string shapeRotate;
    int angle, locationR;
    bool validKey = true;

    line >> shapeRotate;
    locationR = shape_location(shapeRotate);
    if (line.fail()) {
        fewArgs();
        validKey = false;
    } else if (shapeName_validity(shapeRotate) == false) {
        invalidName();
        validKey = false;
    } else if (locationR == -1) {
        nameNotFound(shapeRotate);
        validKey = false;
    } else {

        line >> angle;
        if (line.fail()) {
            if (line.eof()) {
                fewArgs();
                validKey = false;
            } else {
                invalidArg();
                validKey = false;
            }
        } else if (validRotation(angle) == false) {
            invalidValue();
            validKey = false;
        } else {

            string more_arg;
            line >> more_arg;
            if (!line.fail()) {
                manyArgs();
                validKey = false;
            }

        }
    }

    if (validKey == true) {
        shapesArray[locationR]->setRotate(angle);
        cout << "Rotated " << shapeRotate << " by " << angle << " degrees" << endl;
    }
}

void draw(stringstream & line) {
    string shapeDraw;
    int locationD;
    bool validKey = true;

    line >> shapeDraw;
    locationD = shape_location(shapeDraw);
    if (line.fail()) {
        fewArgs();
        validKey = false;
    } 
    //if the argument to draw command was all
    else if (shapeDraw == keyWordsList[0]) {
        string more_arg;
        line >> more_arg;
        if (!line.fail()) {
            manyArgs();
            validKey = false;
        } else {
            cout << "Drew all shapes" << endl;
            for (int i = 0; i < max_shapes; ++i) {
                if (shapesArray[i] != NULL) {
                    shapesArray[i]->draw();
                }
            }
        }
    } else {
        if (shapeName_validity(shapeDraw) == false) {
            invalidName();
            validKey = false;
        } else if (locationD == -1) {
            nameNotFound(shapeDraw);
            validKey = false;
        } else {

            string more_argument;
            line >> more_argument;
            if (!line.fail()) {
                manyArgs();
                validKey = false;
            }

        }

        if (validKey == true) {
            cout << "Drew " << shapesArray[locationD]->getName() << ": "
                    << shapesArray[locationD]->getType() << " " << shapesArray[locationD]->getXlocation() << " "
                    << shapesArray[locationD]->getYlocation() << " " << shapesArray[locationD]->getXsize() << " "
                    << shapesArray[locationD]->getYsize() << endl;

        }
    }
}

void delete_(stringstream & line) {
    string shapeDelete;
    int locationDE;
    bool validKey = true;

    line >> shapeDelete;
    locationDE = shape_location(shapeDelete);
    if (line.fail()) {
        fewArgs();
        validKey = false;
    } 
    //if argument to delete command was all
    else if (shapeDelete == keyWordsList[0]) {
        string more_arg;
        line >> more_arg;
        if (!line.fail()) {
            manyArgs();
            validKey = false;
        } else {

            cout << "Deleted: all shapes" << endl;
            for (int i = 0; i < max_shapes; ++i) {
                if (shapesArray[i] != NULL) {
                    delete shapesArray[i];
                    shapesArray[i] = NULL;
                }
            }
        }
    } else {

        if (locationDE == -1) {
            nameNotFound(shapeDelete);
            validKey = false;
        } else {

            string more_argument;
            line >> more_argument;
            if (!line.fail()) {
                manyArgs();
                validKey = false;
            }
        }


        if (validKey == true) {
            cout << "Deleted shape " << shapesArray[locationDE]->getName() << endl;
            if (shapesArray[locationDE] != NULL) {
                delete shapesArray[locationDE];
                shapesArray[locationDE] = NULL;
            }
        }
    }
}

void invalidCommand() {
    cout << "Error: invalid command" << endl;
}

void invalidArg() {
    cout << "Error: invalid argument" << endl;
}

void invalidName() {
    cout << "Error: invalid shape name" << endl;
}

void nameExists(string shapeN) {
    cout << "Error: shape " << shapeN << " exists" << endl;
}

void nameNotFound(string shapeN) {
    cout << "Error: shape " << shapeN << " not found" << endl;
}

void invalidType() {
    cout << "Error: invalid shape type" << endl;
}

void invalidValue() {
    cout << "Error: invalid value" << endl;
}

void manyArgs() {
    cout << "Error: too many arguments" << endl;
}

void fewArgs() {
    cout << "Error: too few arguments" << endl;
}

void full() {
    cout << "Error: shape array is full" << endl;
}

//check the shape name to be not one of the commands or shape type
bool shapeName_validity(string shape_name) {
    for (int i = 0; i < 7; ++i) {
        if (shape_name == keyWordsList[i]) {
            return false;
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (shape_name == shapeTypesList[i]) {
            return false;
        }
    }
    return true;
}

//check if the shape name entered by user exits or not
bool shapeName_existance(string shape_name) {
    for (int i = 0; i < shapeCount; ++i) {
        if (shapesArray[i] != NULL) {
            if (shape_name == shapesArray[i]->getName()) {
                return false;
            }

        }
    }
    return true;
}

//check the type to be one of the available and valid type
bool shapeType_validity(string shape_type) {
    for (int i = 0; i < 4; ++i) {
        if (shape_type == shapeTypesList[i]) {
            return true;
        }
    }
    return false;
}

//check for the size and location
bool validVal(int loc) {
    if (loc > 0) return true;
    else {
        //invalidValue();
        return false;
    }
}

//get the location of the shape
int shape_location(string shape_name) {
    for (int i = 0; i < shapeCount; ++i) {
        if (shapesArray[i] != NULL) {
            if (shape_name == shapesArray[i]->getName()) {
                return i;
            }

        }
    }
    return -1;
}

//check the rotation angle
bool validRotation(int ang) {
    if (ang < 0 || ang > 360) {
        return false;
    } else return true;
}
