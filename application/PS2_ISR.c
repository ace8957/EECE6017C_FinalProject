#include "globals.h"
#include "keyboard.h"
extern volatile char byte1, byte2, byte3, byte4;
extern volatile char *kbBuf;
extern volatile unsigned int kbBufBegin, kbBufEnd;
extern volatile int change;
extern volatile int packet1;
extern volatile int packetX;
extern volatile int packetY;
extern volatile char keyPressed;
extern volatile int keyboardLock;

/**
 * lookUpKBCode - lookup table for keyboard key codes, based
 * on table from www.computer-engineering.com/ps2keyboard/scancodes2.html.
 * Currently only supports alpha-numerics
 */
char lookUpKBCode(const char scanCode)
{
    switch(scanCode) {
        case 0x1C: return 'a';
        case 0x32: return 'b';
        case 0x21: return 'c';
        case 0x23: return 'd';
        case 0x24: return 'e';
        case 0x2B: return 'f';
        case 0x34: return 'g';
        case 0x33: return 'h';
        case 0x43: return 'i';
        case 0x3B: return 'j';
        case 0x42: return 'k';
        case 0x4B: return 'l';
        case 0x3A: return 'm';
        case 0x31: return 'n';
        case 0x44: return 'o';
        case 0x4D: return 'p';
        case 0x15: return 'q';
        case 0x2D: return 'r';
        case 0x1B: return 's';
        case 0x2C: return 't';
        case 0x3C: return 'u';
        case 0x2A: return 'v';
        case 0x1D: return 'w';
        case 0x22: return 'x';
        case 0x35: return 'y';
        case 0x1A: return 'z';
        case 0x45: return '0';
        case 0x16: return '1';
        case 0x1E: return '2';
        case 0x26: return '3';
        case 0x25: return '4';
        case 0x2E: return '5';
        case 0x36: return '6';
        case 0x3D: return '7';
        case 0x3E: return '8';
        case 0x46: return '9';
		case 0x5A: return '\n';
		case 0x29: return ' ';
        default: return '&';
    }
}


/***************************************************************************************
 * Pushbutton - Interrupt Service Routine                                
 *                                                                          
 * This routine checks which KEY has been pressed. If it is KEY1 or KEY2, it writes this 
 * value to the global variable key_pressed. If it is KEY3 then it loads the SW switch 
 * values and stores in the variable pattern
****************************************************************************************/
void PS2_ISR( void )
{
	static char byteCount = 0;
  	volatile int * PS2_ptr = (int *) 0x10000100;		// PS/2 port address
	int PS2_data, RVALID;
    char lookUpResult;
	static int ackReceived = 0;

	printf("Inside PS2_ISR()\n");
	// if(keyboardLock)
		// return;

	PS2_data = *(PS2_ptr);					// read the Data register in the PS/2 port
	RVALID = (PS2_data & 0x8000);			// extract the RVALID field
	if (RVALID)
	{
		/* always save the last two bytes received */
        byte3 = byte4;
		byte4 = byte2;
		byte2 = PS2_data & 0xFF;
		if ( (byte1 == (char) 0xAA) && (byte2 == (char) 0x00) ) {
			// mouse inserted; initialize sending of data
			*(PS2_ptr) = 0xF4;
            return;
        }
		//if(!ackReceived && byte2 == (char)0xFA)
		//	ackReceived = 1;
        // byte 2 == 0x00 means make key,
		//printf("byte 1 = %x, byte 2 = %x, byte 3 = %x, byte 4 = %x\n",byte1,byte2,byte3,byte4);
		//if(byte2 == (char)0XF0) {
		//	byte3 = byte1;
		//}
		//(byte1 == byte2 || byte2 == (char)0xFFFFFFF0 || byte2 == (char)0xAA || byte3 == byte2 || byte2 == (char)0xFA)
		//	return;
        
        //if (byte2 == byte3 && (byte4 == 0xFFFFFFF0 || byte4 == 0xF0))
        //    keyPressed = byte2;
        
		change = 1;
	}
	return;
}
