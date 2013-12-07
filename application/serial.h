#ifndef SERIAL_H
#define SERIAL_H

#define SERIAL_SUCCESS  0
#define SERIAL_FAIL     1

// API calls
int sendGameBoard(int gameBoard[], int length);
int receiveGameBoard(int gameBoard[], int length);

// Helper functions
int sendSerialMessage(unsigned char);
int tx_Handshake(void);
int rx_Handshake(void);

#endif //SERIAL_H
