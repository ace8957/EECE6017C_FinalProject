// main.c for super group project
// need to add a better header here

// variable definitions and included files
#include "globals.h"
#include "keyboard.h"
#include "nios2_ctrl_reg_macros.h"
#include "serial.h"
#include "game.h"
#include "setup.h"
extern volatile int player_number;
	
#ifndef SERIAL_SHITS
// main function
int main()
{
    int new_game = 1;     // stay zero unless the user decides to start a new game
    int game_mode = 0;
	
	// add setup instructions here
	// initialize serial, vga, ps/2, etc
	// decide player 1 vs player 2 -- maybe we need to get the serial number of the boards
    // or some other available hard coded number and hard code the player one and player two boards
	// so that we dont have to worry about setting up the serial port without knowing who is going
	// to be sending first or receiving first.  this will let it be the same all the time...
	// at least at first.
	
	// main program loop
	while (1){
        if (new_game){
            game_mode = start_new_game(); // call the function to setup a new game, reset new game flag
			new_game = 0; // reset new game flag
			// function call to reset arrays
		}
		
		// player one take turn
		if (player_number == player_two){
			receiveGameBoard();
        }
        if (player_number == player_one){
            //player one takes turn
            take_turn();
            check_status();
		}
		
		// player 2 take turn
		if (player_number == player_one){
            if(game_mode == PLAYER){
                //player 2 waits for ai or human 2
                receiveGameBoard();
            }
            else {
                //ai takes turn
                //ai_make_move();
            }
		}		
		if (player_number == player_two){
            //do player moves
            take_turn();
            check_status();
        }
		
		// game end, quit, or restart
		
	}
	
	return 0;
}
#endif
