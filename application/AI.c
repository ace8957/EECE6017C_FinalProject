#include "globals.h"
#include <string.h>

/*
	The AI will operate on the board which is passed to itself.
	It will make a decision about the position it wishes to attach and
	it will return the index number which it wishes to attack.
	
	The AI will keep track of it's past hits and make decisions based upon
	the likelihood of achieving another hit in proximity to one of those existing
	hits.
	
	The AI will have to decide whether to continue attacking in an enlarging square
	pattern with relation to a point where it does get a hit, or to resort to attempting
	to attack a random position.
	
	A random position to attack can be obtained by calling a helper function get_random_index(),
	which will return an integer between 0-99. The index thus obtained must be check in
	ai_game_board to ensure that we have not already attacked that tile.
	
	The AI will also have to place ships in a somewhat intelligent manner. It may initially
	be hard-coded. This can be accomplished by an ai_place_ships(board) which will accept
	a pointer to a board (the player two board from globals.c?) and place it's ships on said board.
	
	The AI will keep track of it's moves and make decisions by examining a game board,
	which will be a local global kept in this file: ai_game_board[total_board_size-1]. This game
	board will only keep track of hits or misses.
	
	Moves that the AI comes up with must be checked to see if they are a hit or a miss. A helper
	function will be defined ai_check_hit(board, index), which will accept the global master
	copy of the board, and the index which the AI is attacking. The function will then return
	> 0 if a hit is registered, and 0 if the attack was a miss.
	
	The AI will perform its attacks by calling an ai_make_attack(board, index), which will check
	and set the appropriate bits in the master board for player2, and which will also make the
	necessary changes to the local ai_game_board.
	
*/

//externs
extern int player1[total_board_size];
extern int player2[total_board_size];

int initialize_ai(void) {
	//we must set the initial values of our internal game board to 0
	memset(ai_game_board, 0, sizeof(ai_game_board));
	return 0;
}

struct {
	struct node* next;
	int data;
}node;

void ai_place_ships(void) {
	int edges[] = {
				0,1,2,3,4,5,6,7,8,9,
				10,20,30,40,50,60,70,80,90,
				91,92,93,94,95,96,97,98,99,
				19,29,39,49,59,69,79,89
			};
	int random_edge_index = rand() % (sizeof(edges)/sizeof(int));
	
	
	//TODO: get rid of this hard code
	int tmp_board[] = {
        8,8,8,8,8,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        16,0,0,0,0,0,0,64,0,0,
        16,0,0,0,0,0,0,64,0,0,
        16,0,0,0,0,0,0,64,0,0,
        16,0,0,0,0,0,0,0,0,0,
        0,0,0,32,32,32,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,128,
        0,0,0,0,0,0,0,0,0,128,
    };
	memcpy(player2, tmp_board, sizeof(tmp_board));
}

int get_random_index(void) {
	int r;
	//Loop until we get an index which has not already been attacked
	while(1) {
		r = rand() % 100;
		if(ai_game_board[r] == 0)
			break;
	}
	return r;
}

//board - the master copy of the board, probably player2[] from globals.c
int ai_check_hit(int index) {
	if(player1[index] > hit)
		return IS_HIT;
	else
		return IS_MISS;
}

//board - the master copy of the board, probably player2[] from globals.c
void ai_make_attack(int index) {
	if(ai_check_hit(index)) {	
		//set the flag in the ai-only board that is used to make decisions
		ai_game_board[index] = IS_HIT;
		locality_count = 0;
		last_hit = index;
	}
	else {
		//set the flag in the ai-only board that is used to make decisions
		ai_game_board[index] = IS_MISS;
	}
}

int check_valid_index(int index) {
	if(index > 100 || index < 0 || ai_game_board[index])
		return 0;
	return 1;
}

int get_index(start_index, direction) {
	if(direction > 3 || direction < 0)
		return NONE;
	int tmp = 0;
	switch(direction) {
		case 0:	tmp = start_index + 10;
				break;
		case 1: tmp = start_index - 10;
				break;
		case 2: tmp = start_index + 1;
				break;
		case 3: tmp = start_index - 1;
				break;
		default: printf("you done fucked up\n");
	}
	return check_valid_index(tmp) ? tmp : NONE;
}

int ai_make_move(void) {
	int attack_index = NONE;
	
	//check if this is our first move
	if(last_attack == NONE && last_hit == NONE) {
		//it's our first move, so pick a random index to attack
		attack_index = get_random_index();
	}
	else {
		//it's not our first move, check to see if we have gotten a last hit
		//use a counter to check cardinal directions
		if(last_hit && (locality_count < 4)) {
			switch(locality_count) {
				case 0:	attack_index = get_index(last_hit, 0);
						break;
				case 1:	attack_index = get_index(last_hit, 1);
						break;
				case 2:	attack_index = get_index(last_hit, 2);
						break;
				case 3: attack_index = get_index(last_hit, 3);
						break;
				default: printf("you done fucked up\n");
			}
		}
		else {
			attack_index = get_random_index();
		}
	}
	if(attack_index == NONE)
		attack_index = get_random_index();
	last_attack = attack_index;
	ai_make_attack(attack_index);
	return attack_index;
}
