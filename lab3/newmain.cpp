//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

/*
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

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
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
bool validLocation(int ang);

int main() {

    string line;
    string command;
    int prev_count = -1;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input
    
    
    

    while ( !cin.eof() ) {
        
        bool validKeyword = true;
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        //maxShapes
        if (command == keyWordsList[1]){
            
            lineStream >> max_shapes;
        
            if (lineStream.fail() || max_shapes < 0){
                if (lineStream.eof()){
                    validKeyword = false;
                    //cout << validKeyword << endl;
                    lineStream.clear();
                }
                else {
                    invalidValue();
                    lineStream.clear();
                    lineStream.ignore(10000, '\n');
                }
            }
            else {
                if (prev_count == -1){
                    prev_count = max_shapes;
                    shapesArray = new Shape*[max_shapes];
                    //initializing each element to NULL
                    for (int i = 0; i < max_shapes; ++i){
                        shapesArray[i] = NULL;
                    }
                    cout << "New database: max shapes is " << max_shapes << endl;
                }
                else {
                    shapeCount = 0;
                    for (int i = 0; i < prev_count; ++i){
                        if (shapesArray[i] != NULL){
                            delete shapesArray[i];
                            shapesArray[i] = NULL;
                        }
                    }
                    delete [] shapesArray;
                    shapesArray = NULL;
                    prev_count = max_shapes;
                    shapesArray = new Shape*[max_shapes];
                    //initializing each element to NULL
                    for (int i = 0; i < max_shapes; ++i){
                        shapesArray[i] = NULL;
                    }
                    cout << "New database: max shapes is " << max_shapes << endl;
                    }
                }
        }
        //create
        else if (command == keyWordsList[2]){
            string shapeName, shapeType;
            int locationX, locationY, sizeX, sizeY;
            bool validKey = true;
            
            lineStream >> shapeName;
            
            if (lineStream.fail()){
                fewArgs();
                validKey = false;
            }
            
            else if (shapeName_validity(shapeName) == false){
                invalidName();
                validKey = false;
            }
            else if (shapeName_existance(shapeName) == false){
                nameExists(shapeName);
                validKey = false;
            }
            //shapesArray[shapeCount]->setName(shapeName);
            else {
                lineStream >> shapeType;
            
                if (lineStream.fail()){
                    fewArgs();
                    validKey = false;
                }
            
                else if (shapeType_validity(shapeType) == false){
                    invalidType();
                    validKey = false;
                }
            //shapesArray[shapeCount]->setType(shapeType);
                else {
            
                    lineStream >> locationX;
                    if (lineStream.fail()){
                        if (lineStream.eof()){
                            fewArgs();
                            validKey = false;
                        }
                        else {
                            invalidArg();
                            validKey = false;
                        }
                    }
                    else if (validVal(locationX) == false){
                        invalidValue();
                        validKey = false;
                    }
            //shapesArray[shapeCount]->setXlocation(locationX);
                    else {
            
                        lineStream >> locationY;
                        if (lineStream.fail()){
                            if (lineStream.eof()){
                                fewArgs();
                                validKey = false;
                            }
                            else {
                                invalidArg();
                                validKey = false;
                            }
                        }
                        else if (validVal(locationY) == false){
                            invalidValue();
                            validKey = false;
                        }
            //shapesArray[shapeCount]->setYlocation(locationY);
                        else {
            
                            lineStream >> sizeX;
                            if (lineStream.fail()){
                                if (lineStream.eof()){
                                    fewArgs();
                                    validKey = false;
                                }
                                else {
                                    invalidArg();
                                    validKey = false;
                                }
                            }
                            else if (validVal(sizeX) == false){
                                invalidValue();
                                validKey = false;
                            }
            //shapesArray[shapeCount]->setXsize(sizeX);
                            else {
            
                                lineStream >> sizeY;
                                if (lineStream.fail()){
                                    if (lineStream.eof()){
                                        fewArgs();
                                        validKey = false;
                                    }
                                    else {
                                        invalidArg();
                                        validKey = false;
                                    }
                                }
                                else if (validVal(sizeY) == false){
                                    invalidValue();
                                    validKey = false;
                                }
            //shapesArray[shapeCount]->setYsize(sizeY);
                                else if (shapeType == shapeTypesList[0]){
                                    if (sizeX != sizeY){
                                        invalidValue();
                                        validKey = false;
                                    }
                                    else if (shapeCount >= max_shapes){
                                        //cout << "shape count is: " << shapeCount << " and " << "max shape is: " << max_shapes << endl;
                                        full();
                                        validKey = false;
                                    }
                                    else {
                                        string morearg00;                                        
                                        lineStream >> morearg00;
                                        //cout << "more args: " << morearg00 << endl;
                                        if (!lineStream.fail()){
                                            manyArgs();
                                            validKey = false;
                                            }
                                    }
                                }

                                //check the array if it is full or not
                                else if (shapeCount >= max_shapes){
                                    //cout << "shape count is: " << shapeCount << " and " << "max shape is: " << max_shapes << endl;
                                    full();
                                    validKey = false;
                                }
                                else {
                                    string morearg0;
                                    
                                    lineStream >> morearg0;
                                    //cout << "more args: " << morearg0 << endl;
                                    if (!lineStream.fail()){
                                        manyArgs();
                                        validKey = false;
                                        }
                                }
                            }
                        }
                    }
                }
            }
            
            if (validKey == true){
                shapesArray[shapeCount] = new Shape(shapeName, shapeType, locationX, sizeX, locationY, sizeY);
                // cout << "Created " << shapeName << ": " << shapeType << " " << locationX << " " << locationY << " " << sizeX << " " << sizeY << endl;
                cout << "Created " << shapesArray[shapeCount]->getName() << ": " << shapesArray[shapeCount]->getType() << " " << shapesArray[shapeCount]->getXlocation() << " " << shapesArray[shapeCount]->getYlocation() << " " << shapesArray[shapeCount]->getXsize() << " " << shapesArray[shapeCount]->getYsize() << endl;             

                shapeCount++;
                //cout << "shapeCount after creation is: " << shapeCount << endl;
            }
        }
        //move
        else if (command == keyWordsList[3]){
            string shapeMove;
            int locationXMove, locationYMove, location;
            bool validKey1 = true;
            
            lineStream >> shapeMove;
            location = shape_location(shapeMove);
            
            if (lineStream.fail()){
                fewArgs();
                validKey1 = false;
            }
            else if(shapeName_validity(shapeMove) == false){
                invalidName();
                validKey1 = false;
            }
            else if (location == -1){
                nameNotFound(shapeMove);
                validKey1 = false;
                }
            else {
                lineStream >> locationXMove;
                if (lineStream.fail()){
                    if (lineStream.eof()){
                        fewArgs();
                        validKey1 = false;
                    }
                    else {
                        invalidArg();
                        validKey1 = false;
                    }
                }
                else if (validVal(locationXMove) == false){
                    invalidValue();
                    validKey1 = false;
                }
                else {
            
                    lineStream >> locationYMove;
                    if (lineStream.fail()){
                        if (lineStream.eof()){
                            fewArgs();
                            validKey1 = false;
                        }
                        else {
                            invalidArg();
                            validKey1 = false;
                        }
                    }
                    else if (validVal(locationYMove) == false){
                        invalidValue();
                        validKey1 = false;
                    }
                    else {
            
                        string morearg1;
                        lineStream >> morearg1;
                        if (!lineStream.fail()){
                            manyArgs();
                            validKey1 = false;
                        }
                        
                    }
                }
            }
            
            if (validKey1 == true){
                shapesArray[location]->setXlocation(locationXMove);
                shapesArray[location]->setYlocation(locationYMove);
                cout << "Moved " << shapeMove << " to " << locationXMove << " " << locationYMove << endl;            
            }
        }
        //rotate
        else if (command == keyWordsList[4]){
            string shapeRotate;
            int angle, locationR;
            bool validKey2 = true;
            
            lineStream >> shapeRotate;
            locationR = shape_location(shapeRotate);
            if (lineStream.fail()){
                fewArgs();
                validKey2 = false;
            }
            else if(shapeName_validity(shapeRotate) == false){
                invalidName();
                validKey2 = false;
            }
            
            else if (locationR == -1){
                nameNotFound(shapeRotate);
                validKey2 = false;
            }
            else { 
            
                lineStream >> angle;
                if (lineStream.fail()){
                    if (lineStream.eof()){
                        fewArgs();
                        validKey2 = false;
                    }
                    else {
                        invalidArg();
                        validKey2 = false;
                    }
                }
                else if (validLocation(angle) == false){
                    invalidValue();
                    validKey2 = false;
                }
                else { 
            
                    string morearg2;
                    lineStream >> morearg2;
                    if (!lineStream.fail()){
                        manyArgs();
                        validKey2 = false;
                    }
                    
                }
            }
            
            if (validKey2 == true){
                shapesArray[locationR]->setRotate(angle);
                cout << "Rotated " << shapeRotate << " by " << angle << " degrees" << endl;             
            }
        }
        //draw
        else if (command == keyWordsList[5]){
            string shapeDraw;
            int locationD;
            bool validKey3 = true;
            
            lineStream >> shapeDraw;
            locationD = shape_location(shapeDraw);
            if (lineStream.fail()){
                fewArgs();
                validKey3 = false;
            }
            
            else if (shapeDraw == keyWordsList[0]){
                string morearg6;
                lineStream >> morearg6;
                if (!lineStream.fail()){
                    manyArgs();
                    validKey3 = false;
                }
                else {
                    cout << "Drew all shapes" << endl;
                    for (int i = 0; i < max_shapes; ++i){
                        if (shapesArray[i] != NULL){
                            shapesArray[i]->draw();
                        }
                    }
                }
                }
            
            else  {
                if(shapeName_validity(shapeDraw) == false){
                    invalidName();
                    validKey3 = false;
                }
            
                else if (locationD == -1){
                    nameNotFound(shapeDraw);
                    validKey3 = false;
                }
                else {
                
                    string morearg3;
                    lineStream >> morearg3;
                    if (!lineStream.fail()){
                        manyArgs();
                        validKey3 = false;
                    }
                    
                }
                
                if (validKey3 == true){
                    //cout << "location of draw: " << locationD << endl;
                    //shapesArray[locationD]->draw();
                    cout << "Drew " << shapesArray[locationD]->getName() << ": " << shapesArray[locationD]->getType() << " " << shapesArray[locationD]->getXlocation() << " " << shapesArray[locationD]->getYlocation() << " " << shapesArray[locationD]->getXsize() << " " << shapesArray[locationD]->getYsize() << endl;             
                
                }
            }
            
        }
        //delete
        else if (command == keyWordsList[6]){
            string shapeDelete;
            int locationDE;
            bool validKey4 = true;
    
            lineStream >> shapeDelete;
            locationDE = shape_location(shapeDelete);
            if (lineStream.fail()){
                fewArgs();
                validKey4 = false;
            }
    
            else if (shapeDelete == keyWordsList[0]){
                string morearg7;
                lineStream >> morearg7;
                if (!lineStream.fail()){
                    manyArgs();
                    validKey4 = false;
                }
                else {
                    
                    cout << "Deleted: all shapes" << endl;
                    for (int i = 0; i < max_shapes; ++i){
                        if (shapesArray[i] != NULL){
                            delete shapesArray[i];
                            shapesArray[i] = NULL;
                        }
                    }
                    //delete [] shapesArray;
                    //shapesArray = NULL;
                }
                }
            
            else {
                
                if (locationDE == -1){
                    nameNotFound(shapeDelete);
                    validKey4 = false;
                }
                else {
        
                    string moreArg3;
                    lineStream >> moreArg3;
                    if (!lineStream.fail()){
                        manyArgs();
                        validKey4 = false;
                    }
                }
            
                
                if (validKey4 == true){
                    //cout << "location of delete is: " << locationDE << endl;
                    cout << "Deleted shape " << shapesArray[locationDE]->getName() << endl;             
                    if (shapesArray[locationDE] != NULL){
                        delete shapesArray[locationDE];
                        shapesArray[locationDE] = NULL;
                    }
                }
            }
        }
        else {
            invalidCommand();
        }
        
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;

}

void invalidCommand(){
    cout << "Error: invalid command" << endl;
}

void invalidArg(){
    cout << "Error: invalid argument" << endl;
}

void invalidName(){
    cout << "Error: invalid shape name" << endl;
}

void nameExists(string shapeN){
    cout << "Error: shape " << shapeN << " exists" << endl;
}

void nameNotFound(string shapeN){
    cout << "Error: shape " << shapeN << " not found" << endl;
}

void invalidType(){
    cout << "Error: invalid shape type" << endl;
}

void invalidValue(){
    cout << "Error: invalid value" << endl;
}

void manyArgs(){
    cout << "Error: too many arguments" << endl;
}

void fewArgs(){
    cout << "Error: too few arguments" << endl;
}

void full(){
    cout << "Error: shape array is full" << endl;
}

bool shapeName_validity(string shape_name){
    for (int i = 0; i < 7; ++i){
        if (shape_name == keyWordsList[i]){
            return false;
        }
    }
    for (int i = 0; i < 4; ++i){
        if (shape_name == shapeTypesList[i]){
            return false;        
        }
    }
    return true;
}

bool shapeName_existance(string shape_name){
    for (int i = 0; i < shapeCount; ++i){
        if(shapesArray[i] != NULL){
            if(shape_name == shapesArray[i]->getName()){
                //cout << "Error: shape " << shapeName << " exists" << endl;
                //nameExists(shape_name);
                return false;
            }
               
        }
    }
    return true;
}

bool shapeType_validity(string shape_type){
    for (int i = 0; i < 4; ++i){
        if (shape_type == shapeTypesList[i]){
            return true;        
        }
    }
    return false;
}

bool validVal(int loc){
    if (loc > 0) return true;
    else {
        //invalidValue();
        return false;
    }
}

int shape_location(string shape_name){
    for (int i = 0; i < shapeCount; ++i){
        if(shapesArray[i] != NULL){
            if(shape_name == shapesArray[i]->getName()){
                //cout << "Error: shape " << shapeName << " exists" << endl;
                //nameExists(shape_name);
                return i;
            }
               
        }
    }
    return -1;
}

bool validLocation(int ang){
    if (ang < 0 || ang > 360){
        return false;
    }
    else return true;
}
*/