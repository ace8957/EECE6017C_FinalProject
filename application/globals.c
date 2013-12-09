#include "globals.h"

/* global variables */
volatile char byte1, byte2, byte3, byte4;				// PS/2 variables
volatile char packet1, packetX, packetY;		//part of the PS/2 mouse packets
volatile char kbBuf[KB_BUF_SIZE];             // Keyboard input buffer
volatile unsigned int kbBufBegin = 0;
volatile unsigned int kbBufEnd = 0;
volatile int change;							//ps/2 bool flag for buffer change

volatile int timeout;								// used to synchronize with the timer


volatile int player_number = 1; // default player 1

/*
	array element defines:
	0-9:	row A columns 0-9
	10-19:	row B columns 0-9
	20-29:	row C columns 0-9
	30-39:	row D columns 0-9
	40-49:	row E columns 0-9
	50-59:	row F columns 0-9
	60-69:	row G columns 0-9
	70-79:	row H columns 0-9
	80-89:	row I columns 0-9
	90-99:	row J columns 0-9
	
	element 100 bits:
	bit	value	meaning
	-----------------------------
	0:	1		carrier sunk
	1:	2		battleship sunk
	2:	4		submarine sunk
	3:	8		cruiser sunk
	4:	16		destroyer sunk
	-----------------------------
	5:	32		carrier placed
	6:	64		battleship placed
	7:	128		submarine placed
	8:	256		cruiser placed
	9:	512		destroyer placed
	-----------------------------
	10-31;	undefined
	
*/
int player1[total_board_size];
int player2[total_board_size];
int player1_copy[total_board_size];
int player2_copy[total_board_size];
