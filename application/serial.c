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
 * @param gameBoard[] The array with the game board to be overwritten with the
 *                    updated game board.
 * @param length      The length of the array.
 * 
 * @ret int A status code
 *  SERIAL_SUCCESS - the game board was sent successfuly
 *  SERIAL_FAIL - the game board failed to send.
 */
int sendGameBoard(int gameBoard[], int length)
{
    int i = 0;
    char charGameBoard[total_board_size-1];
    
    // Here we are converting our interger game board to characters to be tranfered over serial
    for (i = 0; i < length; i++)
    {
        charGameBoard[i] = (char)(((int)'0')+gameBoard[i]);
    }

    // First establish a handshake with the other game board.
    tx_Handshake();
    printf("tx_Handshake established!\n");
    
    // Now we can send the gameboard over one character at a time
    for (i = 0; i < length; i++)
    {
        sendSerialMessage(charGameBoard[i]);
    }
    
    // Now send the new line character that the other board is looking for
    sendSerialMessage('\n');
    
    return SERIAL_SUCCESS;
}

/* API Function: receiveGameBoard()
 * 
 * This call will wait until the partner board sends the other game board.
 * Once it receives the board it will overwrite the array that was passed in
 * with the updated game board.
 * 
 * @param gameBoard[] The array with the game board to be overwritten with the
 *                    updated game board.
 * @param length      The length of the array.
 * 
 * @ret int A status code
 *  SERIAL_SUCCESS - the game board was received successfuly
 *  SERIAL_FAIL - the game board failed to receive.
 */
int receiveGameBoard(int gameBoard[], int length)
{
    unsigned int data_reg;
    unsigned char *data;
    unsigned int pe = 0;
    int retVal;
    char charGameBoard[100];
    int messageReceived = 0;
    int idx = 0, i = 0;
    
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
                charGameBoard[idx] = (char)(*data);
                idx++;
            }
        }
    }

    // We did not receive the correct number of bits!
    if (idx != length)
        return SERIAL_FAIL;
        
    // Overwrite the existing game board with updated one
    for (i = 0; i < length; i++)
    {
        gameBoard[i] = (int)charGameBoard[i];
        if (i % 10 == 0)
            printf("\n");
        printf("%d,", gameBoard[i]);
    }
    printf("\n");
    
    // Printing out the game board just for testing purposes
    for (i = 0; i < idx; i++)
    {
        if (i % 10 == 0)
            printf("\n");
        printf("%c,", (char)charGameBoard[i]);
    }
    
    return SERIAL_SUCCESS;
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
}

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

    return 1;
}
