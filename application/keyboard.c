#include "keyboard.h"

volatile char keyPressed;

// This function will return the most recent key pressed
int getKey(void)
{
    while (1)
    {
        if (keyPressed == UP)
        {
            keyPressed = 0x00;
            return UP;
        }
        else if (keyPressed == DOWN)
        {
            keyPressed = 0x00;
            return DOWN;
        }
        else if (keyPressed == RIGHT)
        {
            keyPressed = 0x00;
            return RIGHT;
        }
        else if (keyPressed == LEFT)
        {
            keyPressed = 0x00;
            return LEFT;
        }
    }
}