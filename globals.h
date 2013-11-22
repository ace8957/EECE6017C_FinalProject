// globals.h
// add a better header here

#define	carrier_size	5
#define battleship_size	4
#define submarine_size	3
#define cruiser_size	3
#define destroyer_size	2
#define board_size      10

#define cursor_start_x	0	// x-axis coordinate of cursor starting position
#define cursor_start_y	0	// y-axis coordinate of cursor starting position

typedef struct Position     Position;
typedef struct Carrier      Carrier;
typedef struct Battleship   Battleship;
typedef struct Submarine    Submarine;
typedef struct Cruiser      Cruiser;
typedef struct Destroyer    Destroyer;

/** struct Position: used to contain x,y coordinates of 10,10 grid and status of grid position*/
struct Position {
    int x=0;
    int y=0;
    int status=0;//0=water, 1=hit, 2=miss
};

struct Carrier {
    //contains the positions that the Carrier is on
    Position positions[carrier_size];
};

struct Battleship {
    Position positions[battleship_size];
};

struct Submarine {
    Position positions[submarine_size];
};

struct Cruiser {
    Position positions[cruiser_size];
};

struct Destroyer {
    Position positions[destroyer_size];
};

struct Board {
    Position positions[board_size][board_size];
};
