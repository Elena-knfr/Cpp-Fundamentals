//
//  globals.h
//  TicTacToe
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.

#ifndef globals_h
#define globals_h

// Some basic definitions for the game
#define X     1
#define O    -1
#define Empty 0

#define boardSize 3

// Forward declaration of the class GameState (defined in GameState.h)
class GameState;

// The prototype of the playMove function
void playMove(GameState&);

#endif /* globals_h */
