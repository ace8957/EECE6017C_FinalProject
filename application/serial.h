#ifndef SERIAL_H
#define SERIAL_H

#define SERIAL_SUCCESS  0
#define SERIAL_FAIL     1

// API calls
int sendGameBoard(int *p_GameBoard);
int* receiveGameBoard(void);

// Helper functions
int sendSerialMessage(unsigned char);
int tx_Handshake(void);
int rx_Handshake(void);
unsigned rs232_get_available_space_in_write_FIFO(void);

#endif //SERIAL_H
