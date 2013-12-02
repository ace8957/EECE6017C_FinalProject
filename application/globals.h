#ifndef GLOBALS_H
#define GLOBALS_H 1

#define KB_BUF_SIZE     256     // Maximum size of the keyboard buffer

//ship sizes
#define carrier_size    5
#define battleship_size 4
#define submarine_size  3
#define cruiser_size    3
#define destroyer_size  2

#define number_of_ships	5

//board size 101: 100 for the board and 1 for status of remaining ships
#define total_board_size 101
#define board_size		 10
//board values: values for the status of the board
#define water       0
#define miss        2
#define hit         4
#define carrier     8
#define battleship  16
#define submarine   32
#define cruiser     64
#define destroyer   128

#define x_axis	0
#define y_axis	1

#define player_one 1
#define player_two 2

//define game mode
#define AI 0
#define PLAYER 1

//#define SERIAL_SHITS 1

#endif //GLOBALS_H
