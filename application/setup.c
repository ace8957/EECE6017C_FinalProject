

#include "setup.h"
#include "globals.h"
#include "keyboard.h"

#define initial_position	0

void reset_player_arrays();

extern volatile int player_number;
extern volatile int player1[total_board_size];
extern volatile int player2[total_board_size];

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
	if (player_number == player_two){
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
	int ship_size[number_of_ships] = {carrier_size, battleship_size, submarine_size, cruiser_size, destroyer_size};
	int current_length_max; // coincides with maximum amount of movement of ship longways
	int current_width_max; // coincides with maximum amount of ship movement sideways
	int vertical = 0; // 0 for ship along x-axis, 1 for ship along y-axis
	int ship_position[2] = {initial_position, initial_position}; // start at 0,0 -> A0
	int key_value = NOP; // the key value from the keyboard
	int i;
	
	
	for (i=0; i<number_of_ships;i++){
		current_length_max = board_size - ship_size[i];
		current_width_max = board_size - 1;
		
		while(key_value != ENTER){
			key_value = getKey();
			switch (key_value){
				case UP:
					if (ship_position[y_axis] > 0)					
						ship_position[y_axis] = ship_position[y_axis] - 1;
					break;
				case DOWN:
					if (vertical)
						if (ship_position[y_axis] < current_length_max)
							ship_position[y_axis] = ship_position[y_axis] + 1;
					else
						if (ship_position[y_axis] < current_width_max)
							ship_position[y_axis] = ship_position[y_axis] + 1;					
					break;
				case LEFT:
					if (ship_position[x_axis] > 0)
						ship_position[x_axis] = ship_position[x_axis] - 1;
					break;
				case RIGHT:
					// check location of ship for valid movement
					// if valid
					if (!vertical)
						if (ship_position[x_axis] < current_length_max)
							ship_position[x_axis] = ship_position[x_axis] + 1;
					else
						if (ship_position[x_axis] < current_width_max)
							ship_position[x_axis] = ship_position[x_axis] + 1;
					break;
				case SPACE:
					// check ship position and size
					// switch ship orientation
					if(vertical)
						if (ship_position[x_axis] < current_length_max)						
							vertical = 0;
					else
						if (ship_position[y_axis] < current_length_max)
							vertical = 1;
					break;
				default:
					break;
			}
		}
		
		
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