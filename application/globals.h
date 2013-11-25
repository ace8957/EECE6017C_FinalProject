#ifndef GLOBALS_H
#define GLOBALS_H 1

#define KB_BUF_SIZE     256     // Maximum size of the keyboard buffer

//ship sizes
#define carrier_size    5
#define battleship_size 4
#define submarine_size  3
#define cruiser_size    3
#define destroyer_size  2

//board size 101: 100 for the board and 1 for status of remaining ships
#define board_size 101

//board values: values for the status of the board
#define water       0
#define miss        2
#define hit         4
#define carrier     8
#define battleship  16
#define submarine   32
#define cruiser     64
#define destroyer   128

/*
	array element defines:
	0-9:	row A columns 1-10
	10-19:	row B columns 1-10
	20-29:	row C columns 1-10
	30-39:	row D columns 1-10
	40-49:	row E columns 1-10
	50-59:	row F columns 1-10
	60-69:	row G columns 1-10
	70-79:	row H columns 1-10
	80-89:	row I columns 1-10
	90-99:	row J columns 1-10
	
	element 100 bits:
	0-4:	00000 carrier hits
	5-9:	X0000 battleship hits
	10-14:	XX000 submarine hits
	15-19:	XX000 cruiser hits
	20-24:	XXX00 destroyer hits
	25-31;	XXXXXXX undefined
*/
int player1[board_size];
int player2[board_size];


#endif //GLOBALS_H
