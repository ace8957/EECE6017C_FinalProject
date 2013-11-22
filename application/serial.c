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
 
int sendSerialMessage(char msg)
{
    volatile int * RS232_data_ptr = (int *) 0x10001010; // RS232 data register address
    volatile int * RS232_ctrl_ptr = (int *) 0x10001030; // RS232 control register address
    
    int data_mask = 0xFFFF;
    int data = 0xFFFF;
    
    data = data_mask & (int)msg;
    
    printf("data = %x",data);
    
    
    return 1;
}