// main.c for super group project
// need to add a better header here

// variable definitions and included files
#include "globals.h"
#include "keyboard.h"
#include "nios2_ctrl_reg_macros.h"
#include "serial.h"
#include "game.h"
#include "setup.h"

int new_game = 1;  // stay zero unless the user decides to start a new game
extern volatile int player_number;
	
/*
/*
// main function
int main()
{
    int new_game = 1;     // stay zero unless the user decides to start a new game
	int player_count = 1; // default, 1 for AI 2 for 2 player
	int player_turn = 0;  // 0 for player 1, 1 for player 2 or AI
	
	
	// add setup instructions here
	// initialize serial, vga, ps/2, etc
	// decide player 1 vs player 2 -- maybe we need to get the serial number of the boards
    // or some other available hard coded number and hard code the player one and player two boards
	// so that we dont have to worry about setting up the serial port without knowing who is going
	// to be sending first or receiving first.  this will let it be the same all the time...
	// at least at first.
	
	
    // 	initial program start / restart	
	player_count = start_new_game(); // call the function to setup a new game, reset new game flag
	new_game = 0; // reset new game flag
    
	// main program loop
	while (1){
        if (new_game){
            player_count = start_new_game(); // call the function to setup a new game, reset new game flag
			new_game = 0; // reset new game flag
			// function call to reset arrays
		}
		
		// player one take turn
		if (player_number == player_two){
			receiveGameBoard();
		}
		if (player_number == player_one){
			getKey();
			//sendGameBoard();
		}
		
		// player 2 take turn
		if (player_number == player_one){
			receiveGameBoard();
		}		
		if (player_number == player_two){
			getKey();
			//sendGameBoard();
		}
		
		// game end, quit, or restart
		
	}
	
	return 0;
}
*/