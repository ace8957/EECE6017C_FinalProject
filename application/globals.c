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

volatile int myBoard[board_size];
volatile int opBoard[board_size];
