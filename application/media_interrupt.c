#include "nios2_ctrl_reg_macros.h"
#include "globals.h"
#include "keyboard.h"
#include "serial.h"

#define SCREEN_WIDTH 319
#define SCREEN_HEIGHT 239

/* these globals are written by interrupt service routines; we have to declare 
 * these as volatile to avoid the compiler caching their values in registers */
extern volatile char byte1, byte2, byte3;			/* modified by PS/2 interrupt service routine */
extern volatile int record, play, buffer_index;	// used for audio
extern volatile int timeout;							// used to synchronize with the timer
extern volatile char *kbBuf;  // Use to store the keyboard input
extern volatile unsigned int kbBufBegin, kbBufEnd; // Used to keep track of the keyboard input
extern volatile int change;//used to check change of input
extern volatile int packet1;
extern volatile int packetX;
extern volatile int packetY;

int mouseX,
	mouseY,
	lastMouseX = SCREEN_WIDTH/2,
	lastMouseY = SCREEN_HEIGHT/2;
	
const int box_len = 8;

/* function prototypes */
void VGA_subStrn(int, int, volatile char *, unsigned int, unsigned int, unsigned int);
void VGA_text (int, int, char *);
void VGA_box (int, int, int, short);
void fill_screen (int, int, int, int, short);
void HEX_PS2(char, char);

/********************************************************************************
 * This program demonstrates use of the media ports in the DE1 Media Computer
 *
 * It performs the following: 
 *  	1. records audio for about 10 seconds when an interrupt is generated by
 *  	   pressing KEY[1]. LEDG[0] is lit while recording. Audio recording is 
 *  	   controlled by using interrupts
 * 	2. plays the recorded audio when an interrupt is generated by pressing
 * 	   KEY[2]. LEDG[1] is lit while playing. Audio playback is controlled by 
 * 	   using interrupts
 * 	3. Draws a blue box on the VGA display, and places a text string inside
 * 	   the box. Also, moves the word ALTERA around the display, "bouncing" off
 * 	   the blue box and screen edges
 * 	4. Displays the last two bytes of data received from the PS/2 port 
 * 	   on the HEX displays on the DE1 board. The PS/2 port is handled using 
 * 	   interrupts
 * 	5. The speed of refreshing the VGA screen
 * 	   are controlled by interrupts from the interval timer
********************************************************************************/


int main(void)
{
	/* Declare volatile pointers to I/O registers (volatile means that IO load
	   and store instructions will be used to access these pointer locations, 
	   instead of regular memory loads and stores) */
	volatile int * interval_timer_ptr = (int *) 0x10002000;	// interal timer base address
	volatile int * KEY_ptr = (int *) 0x10000050;					// pushbutton KEY address
	volatile int * PS2_ptr = (int *) 0x10000100;					// PS/2 port address
    unsigned int flags = 0;
    

	/* initialize some variables */
	byte1 = 0; byte2 = 0; 			// used to hold PS/2 data
	timeout = 0;										// synchronize with the timer

	/* these variables are used for a blue box and a "bouncing" ALTERA on the VGA screen */
	int ALT_x1; int ALT_x2; int ALT_y; 
	int ALT_inc_x; int ALT_inc_y;
	int blue_x; int blue_y; 
	int screen_x; int screen_y; int char_buffer_x; int char_buffer_y;
	short color;
    const short background_color = 0x1863;
    
    int keyVal = 0;

	/* set the interval timer period for scrolling the HEX displays */
	int counter = 0x960000;				// 1/(50 MHz) x (0x960000) ~= 200 msec
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

	/* create a messages to be displayed on the VGA display */
	char text_top_VGA[20] = "Altera DE1\0";
	char text_bottom_VGA[20] = "Media Computer\0";
	char text_ALTERA[10] = "Altera\0";
	char text_erase[10] = "      \0";


	/* the following variables give the size of the pixel buffer */
	screen_x = SCREEN_WIDTH; screen_y = SCREEN_HEIGHT;
	color = 0x1863;		// a dark grey color
	fill_screen (0, 0, screen_x, screen_y, color);	// fill the screen with grey
    // draw a medium-blue box around the above text, based on the character buffer coordinates
	blue_x = 28; blue_y = 26;
	// character coords * 4 since characters are 4 x 4 pixel buffer coords (8 x 8 VGA coords)
	color = 0x187F;		// a medium blue color

	char_buffer_x = 79; char_buffer_y = 59;
	ALT_x1 = 0; ALT_x2 = 5/* ALTERA = 6 chars */; ALT_y = 0; ALT_inc_x = 0; ALT_inc_y = -4;
    
    
	while (1)
	{
		while (!timeout)
			;	// wait to synchronize with timer 

        VGA_box(blue_x, blue_y, box_len, background_color);
        
        //keyVal = getKey();
        flags = rx_Handshake();
        if (keyVal == UP)
            printf("UP\n");
        else if (keyVal == DOWN)
            printf("DOWN\n");
        else if (keyVal == RIGHT)
            printf("RIGHT\n");
        else if (keyVal == LEFT)
            printf("LEFT\n");

		/* display PS/2 data (from interrupt service routine) on HEX displays */
		/*if(change == 1)
		{
			change = 0;
			VGA_subStrn(0, 0, kbBuf, kbBufBegin, kbBufEnd, KB_BUF_SIZE);
		}*/
		timeout = 0;
	}
}

/****************************************************************************************
 * Subroutine to send a string of text to the VGA monitor 
****************************************************************************************/
void VGA_text(int x, int y, char * text_ptr)
{
	int offset;
  	volatile char * character_buffer = (char *) 0x09000000;	// VGA character buffer
	/* assume that the text string fits on one line */
	offset = (y << 7) + x;
	while ( *(text_ptr) )
	{
		*(character_buffer + offset) = *(text_ptr);	// write to the character buffer
		++text_ptr;
		++offset;
	}
}

char getHexCharacter(const char h) {
    switch(h) {
        case 0x00: return '0';
        case 0x01: return '1';
        case 0x02: return '2';
        case 0x03: return '3';
        case 0x04: return '4';
        case 0x05: return '5';
        case 0x06: return '6';
        case 0x07: return '7';
        case 0x08: return '8';
        case 0x09: return '9';
        case 0x0A: return 'A';
        case 0x0B: return 'B';
        case 0x0C: return 'C';
        case 0x0D: return 'D';
        case 0x0E: return 'E';
        case 0x0F: return 'F';
        default: return '&';
    }
    return '&';
}


void VGA_printKBScanCode(int x, int y) {
    int offset;
  	volatile char * character_buffer = (char *) 0x09000000;	// VGA character buffer
	/* assume that the text string fits on one line */
	offset = (y << 7) + x;
	*(character_buffer + offset) = getHexCharacter((byte2 >> 4) & 0x0F);
    offset++;
    *(character_buffer + offset) = getHexCharacter(byte2 & 0x0F);
}

/****************************************************************************************
 * Subroutine to print a substring to the VGA monitor from a circular buffer
 * x - horizontal location on the screen to start writing the text
 * y - vertical location on the screen to start writing text
 * buffer - circular buffer holding the string to write
 * first - index in the buffer to start writing the string
 * last - index after the last character to write
 * len - length of the buffer
****************************************************************************************/
void VGA_subStrn(int x, int y, volatile char *buffer, unsigned int first, unsigned int last, unsigned int len)
{
	int offset;
  	volatile char * character_buffer = (char *) 0x09000000;	// VGA character buffer
    unsigned int idx = first%len;
    last = last%len;
	/* assume that the text string fits on one line */
	offset = (y << 7) + x;
    while(idx != last)
	{
		*(character_buffer + offset) = buffer[idx];	// write to the character buffer
		++offset;
        idx = (idx+1)%len;
	}
    VGA_printKBScanCode(0, 10);
}

/****************************************************************************************
 * Draw a filled rectangle on the VGA monitor 
****************************************************************************************/
void VGA_box(int x, int y, int len, short pixel_color)
{
	int offset, row, col;
  	volatile short * pixel_buffer = (short *) 0x08000000;	// VGA pixel buffer

	/* assume that the box coordinates are valid */
	for (row = y; row <= y+len; row++)
	{
		col = x;
		while (col <= x+len)
		{
			offset = (row << 9) + col;
			*(pixel_buffer + offset) = pixel_color;	// compute halfword address, set pixel
			++col;
		}
	}
}

/****************************************************************************************
 * Draw a filled rectangle on the VGA monitor 
****************************************************************************************/
void fill_screen(int x1, int y1, int x2, int y2, short pixel_color)
{
	int offset, row, col;
  	volatile short * pixel_buffer = (short *) 0x08000000;	// VGA pixel buffer

	/* assume that the box coordinates are valid */
	for (row = y1; row <= y2; row++)
	{
		col = x1;
		while (col <= x2)
		{
			offset = (row << 9) + col;
			*(pixel_buffer + offset) = pixel_color;	// compute halfword address, set pixel
			++col;
		}
	}
}

/****************************************************************************************
 * Subroutine to show a string of HEX data on the HEX displays
****************************************************************************************/
void HEX_PS2(char b1, char b2)
{
	volatile int * HEX3_HEX0_ptr = (int *) 0x10000020;

	/* SEVEN_SEGMENT_DECODE_TABLE gives the on/off settings for all segments in 
	 * a single 7-seg display in the DE1 Media Computer, for the hex digits 0 - F */
	unsigned char	seven_seg_decode_table[] = {	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 
		  										0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };
	unsigned char	hex_segs[] = { 0, 0, 0, 0};
	unsigned int shift_buffer, nibble;
	unsigned char code;
	int i;

	shift_buffer = (b1 << 8) | b2;
	for ( i = 0; i < 4; ++i )
	{
		nibble = shift_buffer & 0x0000000F;		// character is in rightmost nibble
		code = seven_seg_decode_table[nibble];
		hex_segs[i] = code;
		shift_buffer = shift_buffer >> 4;
	}
	/* drive the hex displays */
	*(HEX3_HEX0_ptr) = *(int *) (hex_segs);
}
