//

//  GameState.cpp

//  TicTacToe

//

//  Created by Tarek Abdelrahman on 2019-06-07.

//  Modified by Tarek Abdelrahman on 2020-09-17.

//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.

#include <iostream>

#include "globals.h"

#include "GameState.h"

#include <string>

using namespace std;

GameState::GameState(){

    selectedRow = 0;

    selectedColumn = 0;

    moveValid = true;

    gameOver = false;

    winCode = 0;

    turn = true;

    for ( int i = 0 ; i < boardSize ; i++ ){

        for ( int j = 0 ; j < boardSize ; j++ ){

            gameBoard[i][j] = Empty;

        }

    }

}

int GameState::get_selectedRow(){

    return selectedRow;

}

int GameState::get_selectedColumn(){

    return selectedColumn;

}

void GameState::set_selectedRow(int value){

    if ( (value < 0) || (value > boardSize-1) ){

        cout << "The selected row is invalid" << endl;

        value = 0;

    }

    else selectedRow = value;

}

void GameState::set_selectedColumn(int value){

    if ( (value < 0) || (value > boardSize-1) ){

        cout << "The selected column is invalid" << endl;

        value = 0;

    }

    else selectedColumn = value;

}

bool GameState::get_moveValid(){

    return moveValid;

}

void GameState::set_moveValid(bool value){

    moveValid = value;

}

bool GameState::get_gameOver(){

    return gameOver;

}

void GameState::set_gameOver(bool value){

    gameOver = value;

}

int GameState::get_winCode(){

    return winCode;

}

void GameState::set_winCode(int value){

    if ( (value < 0) || (value > 8 ) ){

        cout << "The value is out of range ..." << endl;

    }

    else winCode = value;

}

bool GameState::get_turn(){

    return turn;

}

void GameState::set_turn(bool value){

    turn = value;

}

int GameState::get_gameBoard(int row, int col){

    if ( (selectedRow >= 0) && (selectedRow < boardSize ) && (selectedColumn >= 0) && (selectedColumn < boardSize ) ){
        return gameBoard[row][col];
    }

    else{
        return 0;
    }

}

void GameState::set_gameBoard(int row, int col, int value){

    if ( (selectedRow >= 0) && (selectedRow < boardSize ) && (selectedColumn >= 0) && (selectedColumn < boardSize ) ){
        gameBoard[row][col] = value;
    }

}
