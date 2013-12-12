// main.c for super group project
// need to add a better header here

// variable definitions and included files
#include "globals.h"
#include "keyboard.h"
#include "nios2_ctrl_reg_macros.h"
#include "serial.h"
#include "game.h"
#include "setup.h"

extern volatile int player_number;
extern int player1[total_board_size];
extern int player2[total_board_size];
extern int player1_copy[total_board_size];
extern int player2_copy[total_board_size];
extern volatile int timeout;
int counter;


// main function
int main()
{
    /* Declare volatile pointers to I/O registers (volatile means that IO load
	   and store instructions will be used to access these pointer locations, 
	   instead of regular memory loads and stores) */
	volatile int * interval_timer_ptr = (int *) 0x10002000;	// interal timer base address
	volatile int * KEY_ptr = (int *) 0x10000050;					// pushbutton KEY address
	volatile int * PS2_ptr = (int *) 0x10000100;					// PS/2 port address
    unsigned option = 0;
    

    /* initialize some variables */
	timeout = 0;										// synchronize with the timer

    /* set the interval timer period for scrolling the HEX displays */
	counter = 0x960000;				// 1/(50 MHz) x (0x960000) ~= 200 msec
	*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
	*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;

	/* start interval timer, enable its interrupts */
	*(interval_timer_ptr + 1) = 0x7;	// STOP = 0, START = 1, CONT = 1, ITO = 1 
	
	*(KEY_ptr + 2) = 0xE; 			/* write to the pushbutton interrupt mask register, and
											 * set 3 mask bits to 1 (bit 0 is Nios II reset) */

	*(PS2_ptr) = 0xFF; 				/* reset */
	*(PS2_ptr + 1) = 0x1; 			/* write to the PS/2 Control register to enable interrupts */

	NIOS2_WRITE_IENABLE( 0xC3 );	/* set interrupt mask bits for levels 0 (interval
											 * timer), 1 (pushbuttons), 6 (audio), and 7 (PS/2) */

	NIOS2_WRITE_STATUS( 1 );		// enable Nios II interrupts
    
    
    int new_game = 1;     // stay zero unless the user decides to start a new game
    int game_mode = 0;
	
	// add setup instructions here
	// initialize serial, vga, ps/2, etc
	// decide player 1 vs player 2 -- maybe we need to get the serial number of the boards
    // or some other available hard coded number and hard code the player one and player two boards
	// so that we dont have to worry about setting up the serial port without knowing who is going
	// to be sending first or receiving first.  this will let it be the same all the time...
	// at least at first.
	
	// main program loop
	while (1){
    
        while (!timeout)
			;	// wait to synchronize with timer 
            
        if (new_game){
            game_mode = start_new_game(); // call the function to setup a new game, reset new game flag
			new_game = 0; // reset new game flag
			// function call to reset arrays
		}
		
		// player one take turn
		if (player_number == player_two){
			receiveGameBoard(player2, total_board_size);
        }
        if (player_number == player_one){
            //player one takes turn
            take_turn();
            check_status();
			sendGameBoard(player2,total_board_size);
		}
		
		// player 2 take turn
		if (player_number == player_one){
            if(game_mode == PLAYER){
                //player 2 waits for ai or human 2
                receiveGameBoard(player1, total_board_size);
            }
            else {
                //ai takes turn
                //ai_make_move();
            }
		}		
		if (player_number == player_two){
            //do player moves
            take_turn();
            check_status();
			sendGameBoard(player1,total_board_size);
        }
		
		// game end, quit, or 
        timeout = 0;
		
	}
	
	return 0;
}
