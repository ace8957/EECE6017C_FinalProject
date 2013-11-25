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

#endif //GLOBALS_H
