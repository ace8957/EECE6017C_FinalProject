

#include "setup.h"
#include "globals.h"

void reset_player_arrays();


int start_new_game()
{
    // display startup screen, select player menu
	// call graphics function
	
	// select players
		// either 2 players or 1 player against AI
		// global variable will hold status of players
	// number_of_players = graphics_function_return_value
	
	
	
	if (1/*number of players == 2*/){
		// player_number = set_player_number(); // function call
		// enter receive state to wait for users to define player 1
	}
	
	// function call to reset arrays
	reset_player_arrays();	
	
	// place ships on screen in turn
	if (player_number == player2){
		// wait for player one to finish placing ships
		// 
	}
	place_ships();
	
	return 0;
}

void reset_player_arrays()
{
	int i;
	for (i = 0; i<board_size; i++){
		player1[i] = water;
		player2[i] = water;
	}
}

void place_ships()
{
	int ship_size[number_of_ships] = [carrier_size, battleship_size, submarine_size, cruiser_size, destroyer_size];
	int current_ship_length, current_ship_height;
	
	for (i=0; i<number_of_ships;i++){
		current_ship_length = board_size - ship_size[i];
		current_ship_height = 1;
	}
	// player 1 place ships
	// a,d,s,w to move ships
	// space bar to rotate ships
	
	// player 2 place ships
	
	
	
}

/*
int set_player_number()
{
	while (1){
		if (space)
			return 1;
		else if (serial receive)
			return 2;
	}
	return 1;
}

*/