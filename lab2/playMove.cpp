//

//  playMove.cpp

//  TicTacToe

//

//  Created by Tarek Abdelrahman on 2019-06-07.

//  Modified by Tarek Abdelrahman on 2020-09-17.

//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.


#include "globals.h"
#include "GameState.h"


void playMove(GameState& game_state) {

    

    int i = game_state.get_selectedRow();

    int j = game_state.get_selectedColumn();

    if ( game_state.get_gameBoard(i, j) == Empty ){
        game_state.set_moveValid(true);

        if ( game_state.get_turn() == true ){

            game_state.set_gameBoard(i, j, X);

            game_state.set_turn(false);

        }

        else {

            game_state.set_gameBoard(i, j, O);

            game_state.set_turn(true);

        }

    }

    else game_state.set_moveValid(false);


    if ( (game_state.get_gameBoard(0, 0)==X && game_state.get_gameBoard(0, 1)==X && game_state.get_gameBoard(0, 2)==X) ||

        (game_state.get_gameBoard(1, 0)==X && game_state.get_gameBoard(1, 1)==X && game_state.get_gameBoard(1, 2)==X) ||

        (game_state.get_gameBoard(2, 0)==X && game_state.get_gameBoard(2, 1)==X && game_state.get_gameBoard(2, 2)==X) ||

        (game_state.get_gameBoard(0, 0)==X && game_state.get_gameBoard(1, 0)==X && game_state.get_gameBoard(2, 0)==X) ||

        (game_state.get_gameBoard(0, 1)==X && game_state.get_gameBoard(1, 1)==X && game_state.get_gameBoard(2, 1)==X) ||

        (game_state.get_gameBoard(0, 2)==X && game_state.get_gameBoard(1, 2)==X && game_state.get_gameBoard(2, 2)==X) ||

        (game_state.get_gameBoard(0, 0)==X && game_state.get_gameBoard(1, 1)==X && game_state.get_gameBoard(2, 2)==X) ||

        (game_state.get_gameBoard(2, 0)==X && game_state.get_gameBoard(1, 1)==X && game_state.get_gameBoard(2, 0)==X) ){

        game_state.set_gameOver(true);

    }


    else if ( (game_state.get_gameBoard(0, 0)==O && game_state.get_gameBoard(0, 1)==O && game_state.get_gameBoard(0, 2)==O) ||

        (game_state.get_gameBoard(1, 0)==O && game_state.get_gameBoard(1, 1)==O && game_state.get_gameBoard(1, 2)==O) ||

        (game_state.get_gameBoard(2, 0)==O && game_state.get_gameBoard(2, 1)==O && game_state.get_gameBoard(2, 2)==O) ||

        (game_state.get_gameBoard(0, 0)==O && game_state.get_gameBoard(1, 0)==O && game_state.get_gameBoard(2, 0)==O) ||

        (game_state.get_gameBoard(0, 1)==O && game_state.get_gameBoard(1, 1)==O && game_state.get_gameBoard(2, 1)==O) ||

        (game_state.get_gameBoard(0, 2)==O && game_state.get_gameBoard(1, 2)==O && game_state.get_gameBoard(2, 2)==O) ||

        (game_state.get_gameBoard(0, 0)==O && game_state.get_gameBoard(1, 1)==O && game_state.get_gameBoard(2, 2)==O) ||

        (game_state.get_gameBoard(2, 0)==O && game_state.get_gameBoard(1, 1)==O && game_state.get_gameBoard(2, 0)==O) ){

        game_state.set_gameOver(true);

    }

    else game_state.set_gameOver(false);
   
    int count_X_ver = 0;

    int count_O_ver = 0;
    
    int count_X_hor = 0;
    
    int count_O_hor = 0;

    int code_numb = 1;

    if ( game_state.get_gameOver() == true ){
        
        
        if ( ((game_state.get_gameBoard(0, 2)==X) && (game_state.get_gameBoard(1, 1)==X) && (game_state.get_gameBoard(2, 0)==X)) || ((game_state.get_gameBoard(0, 2)==O) && (game_state.get_gameBoard(1, 1)==O) && (game_state.get_gameBoard(2, 0)==O)) ){

            game_state.set_winCode(8);
            }

        else if ( ((game_state.get_gameBoard(0, 0)==X) && (game_state.get_gameBoard(1, 1)==X) && (game_state.get_gameBoard(2, 2)==X)) || ((game_state.get_gameBoard(0, 0)==O) && (game_state.get_gameBoard(1, 1)==O) && (game_state.get_gameBoard(2, 2)==O)) ){

            game_state.set_winCode(7);
            }
    

        for ( int k = 0 ; k < 3 ; k++ ){

            for ( int z = 0 ; z < 3 ; z++ ){

                if ( game_state.get_gameBoard(k, z) == X ){
                    count_X_hor++;
                }
                else if ( game_state.get_gameBoard(k, z) == O ){
                    count_O_hor++;
                }
                
  
            }
            if ( (count_X_hor == 3) || (count_O_hor == 3) ){
                game_state.set_winCode(code_numb);
            }
            code_numb++;
            count_O_hor = 0;
            count_X_hor = 0;
        }
            
        for ( int k = 0 ; k < 3 ; k++ ){

            for ( int z = 0 ; z < 3 ; z++ ){

                if ( game_state.get_gameBoard(z, k) == X ){
                    count_X_ver++;
                }
                else if ( game_state.get_gameBoard(z, k) == O ){
                    count_O_ver++;
                }
  
            }
            if ( (count_X_ver == 3) || (count_O_ver == 3) ){
                game_state.set_winCode(code_numb);
            }
            code_numb++;
            count_O_ver = 0;
            count_X_ver = 0;
        }

       
        if ( game_state.get_winCode() < 1 ){
            game_state.set_winCode(0);
        }
    }
    
    else game_state.set_winCode(0);


}

