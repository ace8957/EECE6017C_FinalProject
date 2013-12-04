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
    int i = 0;
    char testMessage[] = {'1','2','3','2','1','2','3','1','2','3','2','1','2','3','1','2','3','2','1','2','3'};
    
    // First establish a handshake with the other game board.
    tx_Handshake();
    printf("tx_Handshake established!\n");
    
    // Now we can send the gameboard over one character at a time
    for (i = 0; i < 21; i++)
    {
        sendSerialMessage(testMessage[i]);
    }
    
    // Now send the new line character that the other board is looking for
    sendSerialMessage('\n');
    
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
    unsigned int data_reg;
    unsigned char *data;
    unsigned int pe = 0;
    int retVal;
    char gameBoard[100];
    int messageReceived = 0;
    int idx = 0;
    
    // First establish a handshake with the other game board
    rx_Handshake();
    printf("rx_Handshake established!\n");
      
    // Now wait until the full message is received (we know by the new line character)
    while (messageReceived == 0)
    {
        data_reg = __builtin_ldwio(RS232_UART_DATA);
        *data = (data_reg & 0x000001FF);
        retVal = ((data_reg & 0x00008000) >> 15) - 1;
        pe = alt_up_rs232_check_parity(data_reg);
        if (retVal != -1) {
            if (((char)('\n')) == ((char)*data)) // Make sure it is not the last character
            {
                messageReceived = 1;
            }
            else
            {
                gameBoard[idx] = (char)(*data);
                idx++;
            }
            printf("character: %c\n", (char)(*data));
        }
    }   
    
    return 0;
} 

// Helper functions
int alt_up_rs232_check_parity(unsigned int data_reg)
{
	unsigned parity_error = (data_reg & 0x00000200) >> 9;
	return (parity_error ? -1 : 0);
}

int sendSerialMessage(unsigned char msg)
{
    // we should check the fifo here and make sure there is room
    
    
    // we can write directly without thinking about other bit fields for this
    // case ONLY, because only DATA field of the data register is writable
    __builtin_stwio(RS232_UART_DATA, (msg));
}


int rx_Handshake(void) {
	unsigned int data_reg;
    unsigned char *data;
    unsigned int pe = 0;
    int retVal;
    int messageRecieved = 0;
    unsigned char tx_handshake[] = {'t','r','a','n','s','m','i','t','\n','\0'};
    unsigned char rx_handshake[] = {'r', 'e', 'c', 'e', 'i', 'v', 'e'};
    int count = 0;
    
    while (messageRecieved == 0)
    {
        data_reg = __builtin_ldwio(RS232_UART_DATA);
        *data = (data_reg & 0x000001FF);
        retVal = ((data_reg & 0x00008000) >> 15) - 1;
        pe = alt_up_rs232_check_parity(data_reg);
        if (retVal != -1) {
            if (((char)rx_handshake[count]) == ((char)*data))
            {
                count++;
                if (count == 7)
                    messageRecieved = 1;
            }
            else
            {
                count = 0;
            }
            
            printf("data_reg: %h\n", data_reg);
            printf("character: %c\n", (char)(*data));
            printf("parity: %d\n", pe);
        }
    }
    // The handshake has been established so lets send a message back to the computer 
    data = tx_handshake;
    count = 0;
    while(*data) {
        // we can write directly without thinking about other bit fields for this
        // case ONLY, because only DATA field of the data register is writable
        __builtin_stwio(RS232_UART_DATA, (*data));
        *data++;
        // Keep a count of how many bits we have sent. Once we go over the space break
        // from the loop to prevent buffer overflow.
        count++;
        if (count >= 9)
            break;
    }
    // We should be done here so we can continue on
    
    /*
	while(1) {
		data_reg_old = data_reg;
		data_reg = ((*RS232_UART_READ_DATA) & 0x1FF);
        pe = ((*RS232_UART_DATA) & 0x100);
		control_reg = (*RS232_UART_CONTROL);
		// if(data_reg != 0 || control_reg != 0x800000)
			// printf("Data reg: %x, Control reg: %x\n", data_reg, control_reg);
		if(data_reg != data_reg_old)
        {
            printf("RS232_UART_DATA: %x\n", (*RS232_UART_DATA));
            printf("RS232_UART_READ_DATA: %x\n", (*RS232_UART_READ_DATA));
			printf("character: %c\n", (char)data_reg);  
            *RS232_UART_READ_DATA = (*RS232_UART_READ_DATA)&0x80;            
        }
        if (pe != 0)
            printf("PE = 1\n");
	*/
}

unsigned rs232_get_available_space_in_write_FIFO(void)
{
	unsigned char ctrl_reg;
	ctrl_reg = __builtin_ldwio((void *)(((unsigned char*)RS232_UART_DATA) + ((1) * (32/8)))); 
	return (ctrl_reg & 0xFFFF0000) >> 16;
}
/*
unsigned alt_up_rs232_get_used_space_in_read_FIFO(alt_up_rs232_dev *rs232)
{
	alt_u16 ravail = 0;
	// we can only read the 16 bits for RAVAIL --- a read of DATA will discard the data
//	ravail = IORD_16DIRECT(IOADDR_ALT_UP_RS232_DATA(rs232->base), 2); 
	ravail = IORD_ALT_UP_RS232_RAVAIL(rs232->base); 
//	return ravail;
	return (ravail & ALT_UP_RS232_RAVAIL_MSK) >> ALT_UP_RS232_RAVAIL_OFST;
}
*/


int tx_Handshake(void)
{
    unsigned int data_reg;
    unsigned char *data;
    unsigned int pe = 0;
    int retVal;
    int messageRecieved = 0;
    unsigned char tx_handshake[] = {'t','r','a','n','s','m','i','t','\n','\0'};
    unsigned char rx_handshake[] = {'r', 'e', 'c', 'e', 'i', 'v', 'e'};
    int count = 0;

    // First thing we want to do is to send our tx handshake message to the computer.
    data = tx_handshake;
    while(*data) {
        // we can write directly without thinking about other bit fields for this
        // case ONLY, because only DATA field of the data register is writable
        __builtin_stwio(RS232_UART_DATA, (*data));
        *data++;
        // Keep a count of how many bits we have sent. Once we go over the space break
        // from the loop to prevent buffer overflow.
        count++;
        if (count >= 9)
            break;
    }
    
    count = 0;
    // If the the computer reads the message correctly then it will send us a message back.
    while (messageRecieved == 0)
    {
        data_reg = __builtin_ldwio(RS232_UART_DATA);
        *data = (data_reg & 0x000001FF);
        retVal = ((data_reg & 0x00008000) >> 15) - 1;
        pe = alt_up_rs232_check_parity(data_reg);
        if (retVal != -1) {
            if (((char)rx_handshake[count]) == ((char)*data))
            {
                count++;
                if (count == 7)
                    messageRecieved = 1;
            }
            else
            {
                count = 0;
            }
            
            printf("data_reg: %h\n", data_reg);
            printf("character: %c\n", (char)(*data));
            printf("parity: %d\n", pe);
        }
    }
    
    /*
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
    */
    return 1;
}
