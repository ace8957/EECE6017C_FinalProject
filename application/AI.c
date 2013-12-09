#include "globals.h"
#include "AI.h"
#include <string.h>

void print_board(int *board);
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
extern int counter; 

int initialize_ai(void) {
	//we must set the initial values of our internal game board to 0
    int count;
    for(count = 0; count < (total_board_size-1); ++count) {
        ai_game_board[count] = 0;
    }
	return 0;
}

void ai_place_ships(void) {
    printf("in here\n"); 
	int edges[] = {
				0,1,2,3,4,5,6,7,8,9,
				10,20,30,40,50,60,70,80,90,
				91,92,93,94,95,96,97,98,99,
				19,29,39,49,59,69,79,89
			};
    int ships [] = {carrier, battleship, submarine, cruiser, destroyer};
    int sizes [] = {carrier_size, battleship_size, submarine_size, cruiser_size, destroyer_size};
    srand(counter);
	int random_edge_index = rand() % (sizeof(edges)/sizeof(int));
	//int random_edge_index = 4;
    
    printf("ramdom edge index: %d\n", random_edge_index); 
	int direction;
    int index = 0;
    int ship_id = 0;
    int ship_size = 0;
    int start_index = 0;
    int tmp_board [total_board_size];
    
    int count = 0;
    for(count = 0; count < (total_board_size-1); ++count) {
        tmp_board[count] = 0;
    }
    printf("Starting outer while loop\n");
    print_board(tmp_board);
    while(index < 5) {
    printf("Outer while loop: index: %d\n", index);
    ship_id = ships[index];
    ship_size = sizes[index];

    direction = rand() % 3;
    
    //printf("edges index: %d", *(edges+random_edge_index));
    //printf("edges index: %d", edges[random_edge_index]);
    if(index == 0) {
        start_index = rand() % 99; // edges[random_edge_index];
    }
    else {
        start_index = rand() % 99;
    }
    int tmp_index = start_index;
    count = 0;
    while(!check_valid_index(tmp_index, tmp_board) || count < ship_size) { // || check_boarder(ship_id, tmp_index, direction, tmp_board)) {
        printf("Inner while loop: count: %d\n", count);
        //if(!check_valid_index(tmp_index = get_index(tmp_index, direction))) {
        tmp_index = get_index(tmp_index, direction, tmp_board);
        printf("tmp index: %d\n", tmp_index);
        if(tmp_index < 0 || !check_valid_index(tmp_index, tmp_board)){// || !check_boarder(ship_id, tmp_index, direction, tmp_board)) {
            direction = rand() % 3;
            if(index == 0) {
                random_edge_index = rand() % (sizeof(edges)/sizeof(int));
                //start_index = edges[random_edge_index];
                start_index = rand() & 99;
            }
            else {
                start_index = rand() % 99;
            }
            tmp_index = start_index;
            count = 0;
        }
        else {
            ++count;
        }
    }
    count = 0;
    printf("Copying AI board to global player2 board.\n");
    while(count < ship_size) {
        tmp_board[start_index] = ship_id;
        start_index = get_index(start_index, direction, tmp_board);
        count++;
    }
    printf("Printing ship %d or length %d", ship_id, ship_size);
    print_board(tmp_board);
    index++;
    }

	//TODO: get rid of this hard code
	//int tmp_board[] = {
    //    8,8,8,8,8,0,0,0,0,0,
    //    0,0,0,0,0,0,0,0,0,0,
    //    16,0,0,0,0,0,0,64,0,0,
    //    16,0,0,0,0,0,0,64,0,0,
    //    16,0,0,0,0,0,0,64,0,0,
    //    16,0,0,0,0,0,0,0,0,0,
    //    0,0,0,32,32,32,0,0,0,0,
    //    0,0,0,0,0,0,0,0,0,0,
    //    0,0,0,0,0,0,0,0,0,128,
    //    0,0,0,0,0,0,0,0,0,128,
    //};
    printf("setting board\n");
    for(count = 0; count < 100; ++count) {
        player2[count] = tmp_board[count];
    }
    print_board(player2);
}

void print_board(int *board){
    int i = 0;
    for(i; i<100; i++){
        if (i % 10 == 0)
            printf( "\n%d", board[i]);
        else
            printf(" %d ", board[i]);
    }
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

int check_valid_index(int index, int *board) {
	if(index > 99 || index < 0 || board[index])	
        return 0;
	return 1;
}

/*
int check_boarder(int ship, int index, int direction, int *board){
    switch(ship){
        case carrier:
            if (direction == EAST){
                int i;
                for(i=0;i<carrier_size;i++){
                    if(board[i+index]%10 ==0)
                        return 0;
                }
            } else {
                int i;
                for(i=0;i<carrier_size;i++){
                    if(board[index-i]%10 ==0)
                        return 0;
                }
            }
            return 1;
        case battleship:
            if (direction == EAST){
                int i;
                for(i=0;i<battleship_size;i++){
                    if(board[i+index]%10 ==0)
                        return 0;
                }
            } else {
                int i;
                for(i=0;i<battleship_size;i++){
                    if(board[index-i]%10 ==0)
                        return 0;
                }
            }
            return 1;

        case submarine:
            if (direction == EAST){
                int i;
                for(i=0;i<submarine_size;i++){
                    if(board[i+index]%10 ==0)
                        return 0;
                }
            } else {
                int i;
                for(i=0;i<submarine_size;i++){
                    if(board[index-i]%10 ==0)
                        return 0;
                }
            }
            return 1;

        case cruiser:
            if (direction == EAST){
                int i;
                for(i=0;i<cruiser_size;i++){
                    if(board[i+index]%10 ==0)
                        return 0;
                }
            } else {
                int i;
                for(i=0;i<cruiser_size;i++){
                    if(board[index-i]%10 ==0)
                        return 0;
                }
            }
            return 1;

        case destroyer:
            if (direction == EAST){
                int i;
                for(i=0;i<destroyer_size;i++){
                    if(board[i+index]%10 ==0)
                        return 0;
                }
            } else {
                int i;
                for(i=0;i<destroyer_size;i++){
                    if(board[index-i]%10 ==0)
                        return 0;
                }
            }
            return 1;
 
        default: 
            return NONE;
    }
}
*/
                
int get_index(int start_index, int direction, int *board) {
	if(direction > 3 || direction < 0)
		return NONE;
	int tmp = 0;
	switch(direction) {
		case NORTH:	tmp = start_index + 10;
				break;
		case SOUTH: tmp = start_index - 10;
				break;
		case EAST: tmp = start_index + 1;
				break;
		case WEST: tmp = start_index - 1;
				break;
		default: printf("you done fucked up\n");
	}
	return check_valid_index(tmp, board) ? tmp : NONE;
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
				case 0:	attack_index = get_index(last_hit, 0, player2);
						break;
				case 1:	attack_index = get_index(last_hit, 1, player2);
						break;
				case 2:	attack_index = get_index(last_hit, 2, player2);
						break;
				case 3: attack_index = get_index(last_hit, 3, player2);
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

