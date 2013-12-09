#ifndef KEYBOARD_H
#define KEYBOARD_H 1

#define ESC 0x76
#define SPACE 0x29
#define ENTER 0x5A

// We are going to assign w, a, s, d as the movement keys as we would have
// to look at two scan codes for the actual arrows.
#define UP      0x1D   // w
#define DOWN    0x1B   // s
#define RIGHT   0x23   // d
#define LEFT    0x1C   // a
#define ENTER    0x5A   // a

#define ZERO    0x30   // 0
#define ONE    0x31   // 1
#define TWO    0x32   // 2
#define THREE    0x33   // 3
#define FOUR    0x34   // 4
#define FIVE    0x35   // 5
#define SIX    0x36   // 6
#define SEVEN    0x37   // 7
#define EIGHT    0x38   // 8
#define NINE    0x39   // 9

#define NOP    0x00   // nop

int getKey(void);

#endif //KEYBOARD_H
