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

//Global constant definitions
#define IS_HIT 1
#define IS_MISS 0
#define SHIP_MASK 0xF8
#define NONE 999

//externs
extern int player1[total_board_size];
extern int player2[total_board_size];

//Local Globals variables
int ai_game_board[total_board_size-1];
int locality_count = 0;//used to determine the next attack direction when searching around a 
int last_attack = NONE;
int last_hit = NONE;

int initialize_ai(void) {
	//we must set the initial values of our internal game board to 0
	memset(ai_game_board, 0, sizeof(ai_game_board));
	return 0;
}

//board - the master copy of the board, probably player2[] from globals.c
int ai_place_ships(void) {
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
	return 0;
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
		//set the hit flag in the master board
		//FIXME: are we doing bitflags or assigned values?
		player2[index] = hit;//that's a global define from globals.h
		
		//set the flag in the ai-only board that is used to make decisions
		ai_game_board[index] = IS_HIT;
	}
	else {
		//set the miss flag in the master board
		//FIXME: are we doing bitflags or assigned values?
		player2[index] = miss;//that's a global define from globals.h
		
		//set the flag in the ai-only board that is used to make decisions
		ai_game_board[index] = IS_MISS;
	}
}

int ai_get_attack_direction(void) {
	
}

void ai_make_move(void) {
	int attack_index = NONE;
	
	//check if this is our first move
	if(last_attack == NONE && last_hit == NONE) {
		//it's our first move, so pick a random index to attack
		attack_index = get_random_index();
	}
	else {
		//it's not our first move, check to see if we have gotten a last hit
		//use a counter to check cardinal directions
	}
}
