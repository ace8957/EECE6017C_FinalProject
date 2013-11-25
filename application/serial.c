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

#define SYSTEM_BUS_WIDTH 32
/*
 * Data Register 
 */
#define ALT_UP_RS232_DATA_REG			   0

#define ALT_UP_RS232_DATA_DATA_MSK			(0x000001FF)
#define ALT_UP_RS232_DATA_DATA_OFST			(0)
#define ALT_UP_RS232_DATA_RVALID_MSK		(0x00008000)
#define ALT_UP_RS232_DATA_RVALID_OFST		(15)


#define __IO_CALC_ADDRESS_NATIVE(BASE, REGNUM) \
  ((void *)(((unsigned char*)BASE) + ((REGNUM) * (SYSTEM_BUS_WIDTH/8))))
#define IORD_ALT_UP_RS232_DATA(base)		\
		IORD(base, ALT_UP_RS232_DATA_REG)
#define IORD(BASE, REGNUM) \
  __builtin_ldwio (BASE)
  
 
int sendSerialMessage(unsigned char msg)
{
    
    
    // University of Toronto Website - http://www-ug.eecg.toronto.edu/desl/nios_devices/dev_rs232uart.html  
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

int tx_Handshake(void)
{
    unsigned char tx_handshake[] = {'1', '1', '1', '1', '1', '1', '1', '1', '\0'};
    unsigned char rx_handshake[] = {'2', '2', '2', '2', '2', '2', '2', '2', '\0'};
    unsigned char *pOutput;
    
    unsigned int count = 0;
    unsigned char *data = '\0';
    
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
    
    read_data(data);
    
    printf("data = %x", data);
    
    while(1);
    /*while(1)
    {
        printf("data = %x", *RS232_UART_DATA);
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
    */
    return 1;
}

int read_data(unsigned char *data)
{
    unsigned char *pOutput;
    unsigned char rx_data[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
    unsigned int count = 0, overflowFlag = 0;
    unsigned int data_reg;
    pOutput = rx_data;
    data_reg = (*RS232_UART_DATA);//&0x00FF00000;
    printf("data_reg = %x\n", data_reg);
    while ((*RS232_UART_DATA)&0xffff0000)
    {
        overflowFlag = 2;
        if (count < 10)
        {
            count++;
            *pOutput++ = (*RS232_UART_DATA)&0x0000ffff;
        }
        else
        {
            overflowFlag = 1;
            break;
        }
    }
    for (count = 0; count < 10; count++)
    {
        printf("rx_data[%d] = %x\n", count, rx_data);
    }
    printf("overflow = %d",overflowFlag);
    return 0;
    //unsigned char data_reg;
    //data_reg = IORD_ALT_UP_RS232_DATA(RS232_UART_DATA);
    //printf("data_reg = %x\n",data_reg);
    //*data = (data_reg & ALT_UP_RS232_DATA_DATA_MSK) >> ALT_UP_RS232_DATA_DATA_OFST;
	//*parity_error = alt_up_rs232_check_parity(data_reg);
	//return (((data_reg & ALT_UP_RS232_DATA_RVALID_MSK) >> ALT_UP_RS232_DATA_RVALID_OFST) - 1);
}
