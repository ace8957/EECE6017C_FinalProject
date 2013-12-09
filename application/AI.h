#ifndef AI_H
#define AI_H 1

//Global constant definitions
#define IS_HIT 2
#define IS_MISS 1
#define SHIP_MASK 0xF8
#define NONE -1

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

int initialize_ai(void);
void ai_place_ships(void);
int ai_make_move(void);

//Local Globals variables
int ai_game_board[total_board_size-1];
int locality_count = 0;//used to determine the next attack direction when searching around a 
int last_attack = NONE;
int last_hit = NONE;

#endif //AI_H
