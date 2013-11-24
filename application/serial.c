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
#define RS232_UART_CONTROL ((volatile int*) (0x10001010+4))
 
int sendSerialMessage(char msg)
{
    //volatile int * RS232_data_ptr = (int *) 0x10001010; // RS232 data register address
    //volatile int * RS232_ctrl_ptr = (int *) 0x10001030; // RS232 control register address
    
    //int data = 0xFFFF;
    
    //data = *(RS232_data_ptr);  // read the Data register in the RS232 port
    //data = (data & 0xFF00);    // extract the upper 2 bytes from the RS232 data register
    //data  = data | msg;        // write the message to the lower 2 bytes of the data register    
    //*(RS232_data_ptr) = data; // write to the data back into the data register
    
    unsigned char hwld[] = {'H','e','l','l','o',' ','W','o','r','l','d','\0'};
    unsigned char *pOutput;

    pOutput = hwld;
    while(*pOutput) //strings in C are zero terminated
    {
         //if room in output buffer
         if((*RS232_UART_CONTROL)&0xffff0000  ) 
         {
            //then write the next character
            *RS232_UART_DATA = (*pOutput++); 
         }
     }
    return 1;
}
