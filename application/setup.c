

#include "setup.h"
#include "globals.h"
#include "keyboard.h"
#include "serial.h"
#include "ui.h"

#define initial_position	0

void reset_player_arrays();
void place_ships(int player);
void update_ship_position(int, int, int, int, int);
void copy_arrays();
void or_arrays();
void update_screen();

extern volatile int player_number;
extern int player1[total_board_size];
extern int player2[total_board_size];
extern int player1_copy[total_board_size];
extern int player2_copy[total_board_size];

volatile int game_mode = 0;

/**
 * @brief start_new_game - used to start up a new game
 * @return returns the number of players 1 for one player with ai and 2 for serial comm
 */
int start_new_game()
{
    // display startup screen, select player menu

	// select players
		// either 2 players or 1 player against AI
        // global variable will hold status of players
    //for now set to 2 player, so game_mode=0
    int menu_return = MENU_ESCAPE;
    do{
        game_mode = displayMenu("Select game mode", 2, "AI", "Human");
    } while(game_mode == menu_return);
    printf("game mode = %d\n", game_mode);
    if (game_mode == PLAYER){//check if 2 player or one player if 2 player get the player number else player number is 1 and ai will be 2
        do{
            player_number = displayMenu("What player are you?", 2, "Player 1", "Player 2"); // set_player_number(); // function call
        } while(game_mode == menu_return);
		// enter receive state to wait for users to define player 1
	}
    else player_number = 1;//ai mode
	// function call to reset arrays
    printf("player number = %d\n", player_number);
	reset_player_arrays();	
	
    // Now clear the screen for the place ships part
    clearColorBuf();
    clearTextBuf();
    
    // place ships on screen in turn
	if (player_number == player_two){
		// wait for player one to finish placing ships
		//
        receiveGameBoard(player1, total_board_size);
		place_ships(player_two);
	}
	
    if(game_mode == PLAYER) sendGameBoard(player2, total_board_size);

    if(player_number == player_one){
        printf("We are getting here\n");
        if(game_mode == PLAYER) {
			place_ships(player_one);
			sendGameBoard(player1, total_board_size);
			printf("fix me");
			receiveGameBoard(player2, total_board_size);
		}
        else {
            printf("Our AI sucks dick!\n");
            initialize_ai();
            printf("Out init works...\n");
            ai_place_ships();
            displayBoard(player2,1);
        }
    }

    return game_mode;
}

void reset_player_arrays()
{
	int i;
	for (i = 0; i<total_board_size; i++){
		player1[i] = water;
		player2[i] = water;
		player1_copy[i] = water;
		player2_copy[i] = water;
	}
}

void place_ships(int player)
{
	int ship_size[number_of_ships] = {carrier_size, battleship_size, submarine_size, cruiser_size, destroyer_size};
	int current_length_max; // coincides with maximum amount of movement of ship longways
	int current_width_max; // coincides with maximum amount of ship movement sideways
	int vertical = 0; // 0 for ship along x-axis, 1 for ship along y-axis
	int ship_position[2] = {initial_position, initial_position}; // start at 0,0 -> A0
	int key_value = NOP; // the key value from the keyboard
    int i = 0, j = 0, n;//loop variables
    int x, y;// x and y position for checking
    int next_position;//the value to add to get to the next position
    int placed =0;
	int array_position = ship_position[x_axis] + (ship_position[y_axis] * 10);
	int old_array_position = 0;
    int *editBoard;
	
	// print the ship on the screen to start out
	update_ship_position(i, ship_position[x_axis], ship_position[y_axis], vertical, player);
	
	for (i=0; i<number_of_ships;i++){
        ship_position[0] = ship_position[1] = 0;
		placed = 0;
		current_length_max = board_size - ship_size[i];
		current_width_max = board_size - 1;
		// dont move the ship if it is against the sides of the board
        while(!placed){
			key_value = getKey();
			printf("array_position = %d\n", array_position);
			if (array_position == 0){
				player1_copy[ship_size[i]] = water;
			}
			array_position = ship_position[x_axis] + (ship_position[y_axis] * 10);
			update_ship_position(i, array_position, old_array_position, vertical, player);
			switch (key_value){
				case UP:
					if (ship_position[y_axis] > 0) {			
						for (j = 0;j<ship_size[i];j++){
								if (player_number == player_one){
									player1_copy[array_position + j] = water;
								}
								if (player_number == player_two){
									player2_copy[array_position + j] = water;
								}
							}
						old_array_position = array_position + ship_size[i] - 1;
						ship_position[y_axis] = ship_position[y_axis] - 1;
                    }
					break;
				case DOWN:
					if (vertical) {
						if (ship_position[y_axis] < current_length_max){
							old_array_position = array_position;
							ship_position[y_axis] = ship_position[y_axis] + 1;
							for (j = 0;j<ship_size[i];j++){
								if (player_number == player_one){
									player1_copy[array_position + j] = water;
								}
								if (player_number == player_two){
									player2_copy[array_position + j] = water;
								}
							}
						}	
                    }
					else {
						if (ship_position[y_axis] < current_width_max){
							old_array_position = array_position;
							ship_position[y_axis] = ship_position[y_axis] + 1;
							for (j = 0;j<ship_size[i];j++){
								if (player_number == player_one){
									player1_copy[array_position + j] = water;
								}
								if (player_number == player_two){
									player2_copy[array_position + j] = water;
								}
							}
						}
                    }
					break;
				case LEFT:
					if (ship_position[x_axis] > 0){
						old_array_position = array_position + ship_size[i] - 1;
						ship_position[x_axis] = ship_position[x_axis] - 1;
					}
					if (array_position == 0){
						player2_copy[5] = water;
					}
					break;
				case RIGHT:
					if (!vertical) {
						if (ship_position[x_axis] < current_length_max){
							old_array_position = array_position;
							ship_position[x_axis] = ship_position[x_axis] + 1;
						}
                    }
					else {
						if (ship_position[x_axis] < current_width_max){
							old_array_position = array_position;
							ship_position[x_axis] = ship_position[x_axis] + 1;
						}
					}
					break;
				case SPACE:
					// check ship position and size
					// switch ship orientation
					if(vertical) {
						if (ship_position[x_axis] < current_length_max)						
							vertical = 0;
                    }
					else {
						if (ship_position[y_axis] < current_length_max)
							vertical = 1;
                    }
					break;
                case ENTER:
                    x = ship_position[x_axis] + 10*ship_position[y_axis];//position in the array
                    if(player_number == player_one) editBoard = player1;
                    else editBoard = player2;
                    for(n=0;n<ship_size[i];n++){
                        if(editBoard[x] != water){
                            placed = 0;
                            break;//no need to check everything else if this isn't on water
                        }
                        placed =1;
                        if(vertical){//checking by adding to y's
                            x = x + 10;
                            if(x > 100){
                                printf("math error occured\n");
                                placed = 0;
                                break;
                            }
                        }
                        else {
                            x = x + 1;
                            if(x%10 == 0 && (n+1 < ship_size[i])){
                                printf("math2 error occured\n");
                                placed = 0;
                                break;
                            }
                        }
                    }
					printf("player1 array = %d\n",player1);
                    break;
				default:
					break;
			}
        }
    }//end for
}


int set_player_number()
{
    int value;
	while (1){
        value = getKey();
        if(value == SPACE) return player_one;
        else if(value == ESC) return player_two;
	}
    return -1;//error occured
}


void update_ship_position(int ship,int array_position,int old_array_position,int vertical,int player){
	int ship_size[number_of_ships] = {carrier_size, battleship_size, submarine_size, cruiser_size, destroyer_size};
	int current_ship_size = ship_size[ship];
	int moving_array = 0;
	int i = 0; int addition_value = 0;
	int current_ship[number_of_ships] = {carrier, battleship, submarine, cruiser, destroyer};
	
	if (vertical) addition_value = 10;  // for incrementing the row
	else addition_value = 1;  // for incrementing the column

	
	moving_array = 	array_position;
	
	for (i = 0; i<current_ship_size; i++){
		if (player == player_one){
			player1_copy[moving_array] = current_ship[ship];
		}
		if (player == player_two){
			player2_copy[moving_array] = current_ship[i];
		}
		moving_array = moving_array + addition_value; // incremement to the next array position
	}
	
	if ((player == player_one) && (array_position)){
		player1_copy[old_array_position] = water;
	}
	if ((player == player_two) && (array_position)){
		player2_copy[old_array_position] = water;
	}
	//copy_arrays();
	or_arrays();
	update_screen();
}

void copy_arrays(){
	int i = 0;
	
	for (i=0; i<total_board_size; i++){
		player1[i] = player1_copy[i];
		player2[i] = player2_copy[i];
	}
}

void or_arrays(){
	int i = 0;
	
	for (i=0; i<total_board_size-1; i++){
		if (player1[i] != water){
			player1_copy[i] = player1[i];
		}
		if (player2[i] != water){
			player2_copy[i] = player2[i];
		}
	}
}


void update_screen(){
	if (player_number == player_one){
		displayBoard((int *) player1_copy, SHOW_SHIPS);
		displayBoard((int *) player2_copy, NO_SHIPS);
	}
	if (player_number == player_two){
		displayBoard((int *) player2_copy, SHOW_SHIPS);
		displayBoard((int *) player1_copy, NO_SHIPS);
	}
}
