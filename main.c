// main.c for super group project
// need to add a better header here

// variable definitions and included files
#include "globals.h"

int new_game = 0;  // stay zero unless the user decides to start a new game

void start_new_game();

// main function
int main()
{
	/* add setup instructions here */
	// initialize serial, vga, ps/2, etc
	// decide player 1 vs player 2 -- maybe we need to get the serial number of the boards
	// or some other available hard coded number and hard code the player one and player two boards 
	// so that we dont have to worry about setting up the serial port without knowing who is going
	// to be sending first or receiving first.  this will let it be the same all the time...
	// at least at first.
	
	
	/* 	initial program start / restart */	
	start_new_game = new_game(); // call the function to setup a new game, reset new game flag
	
	

	/* main program loop */
	while (1){
		if (start_new_game){
			start_new_game = new_game(); // call the function to setup a new game, reset new game flag
		}
		
		// player one take turn
		// player 2 take turn
		
		// game end, quit, or restart
		
	}
	
	return 0;
}

// set up new game
int start_new_game(){
	// choose player 1 and player 2 - or AI for player 2
	// place ships in turn
    return 0;
}
