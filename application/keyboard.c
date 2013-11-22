#include "keyboard.h"

volatile char keyPressed;
volatile char keyboardLock;

// This function will return the most recent key pressed
int getKey(void)
{
    while (1)
    {
        keyboardLock = 1;
        if (keyPressed == UP)
        {
            keyPressed = 0x00;
            keyboardLock = 0;
            return UP;
        }
        else if (keyPressed == DOWN)
        {
            keyPressed = 0x00;
            keyboardLock = 0;
            return DOWN;
        }
        else if (keyPressed == RIGHT)
        {
            keyPressed = 0x00;
            keyboardLock = 0;
            return RIGHT;
        }
        else if (keyPressed == LEFT)
        {
            keyPressed = 0x00;
            keyboardLock = 0;
            return LEFT;
        }
        keyboardLock = 0;
    }
}