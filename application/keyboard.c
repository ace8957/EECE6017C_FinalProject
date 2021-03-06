#include "keyboard.h"
#include "globals.h"

volatile char keyPressed;
volatile char keyboardLock;

extern volatile char byte1, byte2, byte3, byte4;

// This function will return the most recent key pressed
int getKey(void)
{
    while (1)
    {
        // keyboardLock = 1;
        //printf("byte 1 = %x, byte 2 = %x, byte 3 = %x, byte 4 = %x\n",byte1,byte2,byte3,byte4);
        if (byte2 == byte3)// && (byte4 == (char)0xFFFFFFF0 || byte4 == (char)0xF0))
        {
            keyPressed = byte2;
            break;
        }
        // else
        // {
            // keyboardLock = 0;
        // }
    }
    byte2 = 0x00;
    byte3 = 0x01;
    byte4 = 0x02;
    if (keyPressed == UP)
    {
        keyboardLock = 0;
        return UP;
    }
    else if (keyPressed == DOWN)
    {
        keyboardLock = 0;
        return DOWN;
    }
    else if (keyPressed == RIGHT)
    {
        keyboardLock = 0;
        return RIGHT;
    }
    else if (keyPressed == LEFT)
    {
        keyboardLock = 0;
        return LEFT;
    }
	else if(keyPressed == ESC)
	{
		keyboardLock = 0;
		return ESC;
	}
	else if(keyPressed == ENTER)
	{
		keyboardLock = 0;
		return ENTER;
	}
	else if(keyPressed == ESC)
	{
		keyboardLock = 0;
		return ESC;
	}
	
	else if(keyPressed == ZERO)
	{
		keyboardLock = 0;
		return ZERO;
	}
	else if(keyPressed == ONE)
	{
		keyboardLock = 0;
		return ONE;
	}
	else if(keyPressed == TWO)
	{
		keyboardLock = 0;
		return TWO;
	}
	else if(keyPressed == THREE)
	{
		keyboardLock = 0;
		return THREE;
	}
	else if(keyPressed == FOUR)
	{
		keyboardLock = 0;
		return FOUR;
	}
	else if(keyPressed == FIVE)
	{
		keyboardLock = 0;
		return FIVE;
	}
	else if(keyPressed == SIX)
	{
		keyboardLock = 0;
		return SIX;
	}
	else if(keyPressed == SEVEN)
	{
		keyboardLock = 0;
		return SEVEN;
	}
	else if(keyPressed == EIGHT)
	{
		keyboardLock = 0;
		return EIGHT;
	}
	else if(keyPressed == NINE)
	{
		keyboardLock = 0;
		return NINE;
	}
	else
	{
		keyboardLock = 0;
		return NOP;
	}
}
