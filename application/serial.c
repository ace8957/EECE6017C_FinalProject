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
#define RS232_UART_READ_DATA ((volatile int*) 0x10001012)
#define RS232_UART_CONTROL ((volatile int*) (0x10001014))
 
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
}

int rx_Handshake(void) {
	unsigned int data_reg;
	unsigned int data_reg_old;
	unsigned int control_reg;
	while(1) {
		data_reg_old = data_reg;
		data_reg = ((*RS232_UART_READ_DATA) & 0x7F);
		control_reg = (*RS232_UART_CONTROL);
		// if(data_reg != 0 || control_reg != 0x800000)
			// printf("Data reg: %x, Control reg: %x\n", data_reg, control_reg);
		if(data_reg != data_reg_old)
			printf("character: %c\n", (char)data_reg);
	}
}

int tx_Handshake(void)
{
    unsigned char tx_handshake[] = {'1', '1', '1', '1', '1', '1', '1', '1'};
    unsigned char rx_handshake[] = {'2', '2', '2', '2', '2', '2', '2', '2'};
    unsigned char *pOutput;
    
    unsigned int count = 0;
    
    pOutput = tx_handshake;
    while(*pOutput) //strings in C are zero terminated
    {
         //if room in output buffer
         if((*RS232_UART_CONTROL)&0xffff0000  ) 
         {
            //then write the next character
            *RS232_UART_DATA = (*pOutput++); 
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
