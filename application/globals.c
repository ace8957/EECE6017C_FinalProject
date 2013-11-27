#include "globals.h"

/* global variables */
volatile char byte1, byte2, byte3, byte4;				// PS/2 variables
volatile char packet1, packetX, packetY;		//part of the PS/2 mouse packets
volatile char kbBuf[KB_BUF_SIZE];             // Keyboard input buffer
volatile unsigned int kbBufBegin = 0;
volatile unsigned int kbBufEnd = 0;
volatile int change;							//ps/2 bool flag for buffer change

volatile int timeout;								// used to synchronize with the timer

/*boards*/

volatile int myBoard[total_board_size];
volatile int opBoard[total_board_size];


volatile int player_number = 1; // default player 1

/*
	array element defines:
	0-9:	row A columns 0-9
	10-19:	row B columns 10-19
	20-29:	row C columns 20-29
	30-39:	row D columns 30-39
	40-49:	row E columns 40-49
	50-59:	row F columns 50-59
	60-69:	row G columns 60-69
	70-79:	row H columns 70-79
	80-89:	row I columns 80-89
	90-99:	row J columns 90-99
	
	element 100 bits:
	0-4:	00000 carrier hits
	5-9:	X0000 battleship hits
	10-14:	XX000 submarine hits
	15-19:	XX000 cruiser hits
	20-24:	XXX00 destroyer hits
	25-31;	XXXXXXX undefined
*/
volatile int player1[total_board_size];
volatile int player2[total_board_size];