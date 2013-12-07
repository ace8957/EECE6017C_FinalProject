__author__ = 'Jordan Ross'

import serial

# Prompt the user for the location for the serial for of board 1 and 2.
master_port = raw_input("Please enter the port that the master board is connected to (i.e. COM6):  ")
slave_port = raw_input("Please enter the port that the slave board is connected to (i.e. COM6):   ")

# Open up the serial connections for the two boards.
master_board = serial.Serial(port=master_port, baudrate="115200", bytesize=serial.EIGHTBITS, parity=serial.PARITY_ODD,
                             stopbits=serial.STOPBITS_ONE)

slave_board = serial.Serial(port=slave_port, baudrate="115200", bytesize=serial.EIGHTBITS, parity=serial.PARITY_ODD,
                            stopbits=serial.STOPBITS_ONE)

print("connected to: " + master_board.portstr)
print("connected to: " + slave_board.portstr)

print "Please start the slave board first"
print "Now start the master board"

# The master board is going to be set up to transmit first so we are going to define it as such. The slave board is
# going to be set up to receive first so we are going to define it as such.
tx_Board = master_board
rx_Board = slave_board

#this will store the line
line = []

# The messages that we are going to send and receive respectively.
tx_list = ["t", "r", "a", "n", "s", "m", "i", "t", "\n"]
rx_list = ["r", "e", "c", "e", "i", "v", "e"]

# We are going to start spin waiting until we get the transmit message
messageReceived = True

# The first thing we should expect is a transmit message.
print "We are waiting to read the message from the master board"
while messageReceived:
    for c in tx_Board.read():  # Board 2 should be configured to transmit
        line.append(c)
        if c == '\n':
            print c
            if tx_list[:-1] == line[:-1]:
                print "We got the transmit message"
                line = []
                messageReceived = False
            break

print "Moving on to writing the message to the slave board (configured to receive)"
# Now it is time to send the message to the other board.
for c in rx_list:
    rx_Board.write(c)

print "Waiting until we get the transmit message from the slave board"
messageReceived = True
# Now we wait for the board to send us a message back
while messageReceived:
    for c in rx_Board.read():
        line.append(c)
        if c == '\n':
            if tx_list[:-1] == line[:-1]:
                print "We got the transmit message"
                line = []
                messageReceived = False
            break

# Now we send the message to the board to tell it the board connection is successful.
print "Now send a message to board 2 to tell it that we have received data from board 1"
for c in rx_list:
    tx_Board.write(c)

# Now we are expecting some data to come across the serial port with the last character being the new line character.
# We are going to start spin waiting until we get the entire message

messageReceived = True
print "We are waiting to read data from the master board"
while messageReceived:
    for c in tx_Board.read():  # Board 2 should be configured to transmit
        line.append(c)
        if c == '\n':
            messageReceived = False
            break

for c in line:
    rx_Board.write(c)

master_board.close()
slave_board.close()