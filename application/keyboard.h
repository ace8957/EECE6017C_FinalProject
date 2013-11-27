#ifndef KEYBOARD_H
#define KEYBOARD_H 1

// We are going to assign w, a, s, d as the movement keys as we would have
// to look at two scan codes for the actual arrows.
#define UP      0x1D   	// w
#define DOWN    0x1B   	// s
#define RIGHT   0x23   	// d
#define LEFT    0x1C   	// a
#define ENTER   0x5A   	// a
#define ESC 	0x76 	//esc
#define NOP    	0x00   	// nop
#define SPACE 	0x29

// letters and numbers for turn entry
#define ZERO	0x45	// number 0
#define ONE		0x16	// number 1
#define TWO		0x1E	// number 2
#define THREE	0x26	// number 3
#define FOUR	0x25	// number 4
#define FIVE	0x2E	// number 5
#define SIX		0x36	// number 6
#define SEVEN	0x3D	// number 7
#define EIGHT	0x3E	// number 8
#define NINE	0x46	// number 9

#define LTR_A	0x1C	// letter A
#define LTR_B	0x32	// letter B
#define LTR_C	0x21	// letter C
#define LTR_D	0x23	// letter D
#define LTR_E	0x24	// letter E
#define LTR_F	0x2B	// letter F
#define LTR_G	0x34	// letter G
#define LTR_H	0x33	// letter H
#define LTR_I	0x43	// letter I
#define LTR_J	0x3B	// letter J

int getKey(void);

#endif //KEYBOARD_H
