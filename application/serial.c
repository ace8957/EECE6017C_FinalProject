/* The following information is from the Qsys
 * Baud Rate - 115200
 * Parity - Odd
 * Data bits - 8
 * Stop bits - 1
 * Base Address - 0x10001010
 * IRQ - 10
 */

#include "serial.h"
#include "globals.h"

#define RS232_UART_DATA ((volatile int*) 0x10001010)
#define RS232_UART_READ_DATA ((volatile int*) 0x10001013)
#define RS232_UART_CONTROL ((volatile int*) (0x10001014))

/* API Function: sendGameBoard()
 * 
 * This call will send the game board across the serial port once a handshake
 * has been setup.
 * 
 * @param p_GameBoard   A pointer to the beginning of the game board array.
 * 
 * @ret int A status code
 *  SERIAL_SUCCESS - the game board was sent successfuly
 *  SERIAL_FAIL - the game board failed to send.
 */
int sendGameBoard(int *p_GameBoard)
{
    return SERIAL_SUCCESS;
}

/* API Function: receiveGameBoard()
 * 
 * This call will wait until the partner board sends the other game board.
 * Once it receives the board it will pass back a pointer to beginning of
 * the updated game board.
 * 
 * @ret int* the updated game board.
 */
int* receiveGameBoard(void)
{
    return 0;
} 

// Helper functions
/*
int sendSerialMessage(unsigned char msg)
{
    
    
    // University of Toronto Website
    unsigned char hwld[] = {'H','e','l','l','o',' ','W','o','r','l','d','\0'};
    unsigned char *pOutput;

    pOutput = hwld;
    if (tx_Handshake() == 1)
    {
        return 1;
    }
    else
    {
        while(*pOutput) //strings in C are zero terminated
        {
             //if room in output buffer
             if((*RS232_UART_CONTROL)&0xffff0000  ) 
             {
                //then write the next character
                *RS232_UART_DATA = (*pOutput++); 
             }
         }
        return 0;
    }
	return 1;
}*/

int rx_Handshake(void) {
	unsigned int data_reg;
	unsigned int data_reg_old;
	unsigned int control_reg;
    unsigned int pe = 0;
	while(1) {
		data_reg_old = data_reg;
		data_reg = ((*RS232_UART_READ_DATA) & 0x7F);
        pe = ((*RS232_UART_DATA) & 0x100);
		control_reg = (*RS232_UART_CONTROL);
		// if(data_reg != 0 || control_reg != 0x800000)
			// printf("Data reg: %x, Control reg: %x\n", data_reg, control_reg);
		if(data_reg != data_reg_old)
        {
            printf("RS232_UART_DATA: %x\n", (*RS232_UART_DATA));
            printf("RS232_UART_READ_DATA: %x\n", (*RS232_UART_READ_DATA));
			printf("character: %c\n", (char)data_reg);  
            *RS232_UART_READ_DATA = (*RS232_UART_READ_DATA)*0x80;            
        }
        if (pe != 0)
            printf("PE = 1\n");
	}
}

int tx_Handshake(void)
{
    unsigned char tx_handshake[] = {0x31,0, 0x31, 0, 0x31, 0, 0x31, 0};
    unsigned char rx_handshake[] = {'2', '2', '2', '2', '2', '2', '2', '2'};
    unsigned char *pOutput;
    
    unsigned int count = 0;
    
    while(1)
    {
    pOutput = tx_handshake;
    while(*pOutput) //strings in C are zero terminated
    {
         //if room in output buffer
         if((*RS232_UART_CONTROL)&0xffff0000  ) 
         {
            printf("%x\n",*pOutput);
            printf("%c\n",(char)(0xff & *pOutput));
            //then write the next character
            *RS232_UART_DATA = (*pOutput++); 
         }
    }
    }
    while(1)
    {
        // wait until our data field contains the rx_message;
        if (((*RS232_UART_DATA) & 0x0000ffff ) == 0x00000002)
        {
            count++;
        }
        if (count == 7)
        {
            return 0;
        }
    }
    return 1;
}
