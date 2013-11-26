#include "ui.h"
#include <stdarg.h>
#include "graphics.h"
#include "keyboard.h"

int displayMenu(const char *title, unsigned int numOptions, ...)
{
    int selection = 1;
    char optionList[10][256];
    va_list options;
    va_start(options, numOptions);
    for(int i = 0; i < numOptions; ++i) {
        char *option = va_arg(options, char*);
        strncpy(option[i], option, 256);
    }
    va_end(options);

    
    // Draw the menu background in gray
    drawBox(0, 0, VGA_WIDTH, VGA_HEIGHT, colorRGB(30, 30, 30)); 
    drawBox((VGA_WIDTH/2)-25, 25, 50, numOptions*20, colorRGB(11, 10, 177));
    drawText();
    // Draw the selection background
    // Draw the title
    // Draw the options in their own boxes, with the first option highlighted

    // User wants to display a message box
    if(numOptions == 0) {
        // wait on user input
        char keyPress;
        while(keyPress = getKey()) {
            if(keyPress == ESC) {
                selection = MENU_ESCAPE;
                break;
            }
            else if(keyPress == ENTER) {
                selection = MENU_OK;
                break;
            }
            // ignore other keys, no other options
        }
    }
    else { // Display a menu option
        int selection = 1;

    }
    return selection;


void displayBoard(int board[], int yourBoard)
{
    int x = 1;
    int y = 1;
    int dimension = 120;
    
    if(yourBoard){
        // Draw black box that covers the entire screen
        drawBox(0, 0, VGA_WIDTH, VGA_HEIGHT, colorRGB(0,0,0));
    } else {
        x = dimension;
        y = dimension;
        dimension = 160;
        drawBox(x, y, dimension, dimension, colorRGB(0,0,0));
    }  
    
    // Set the dimension for each individual square (12 or 16 pixels)
    int square = dimension/10;

    // Loop through the board array and color individual squares accordingly
    int i = 0;
    for(i;i<100;i++){
        // Reset x & y corrdinates for a new row
        if(i%10 == 0){
          x = 1;
          y = y+square+1;
        }
        // Water - Red
        if(board[i] == 0) drawBox(x, y, square, square, colorRGB(0,0,255));      
        // Miss - White
        if(board[i] == 2) drawBox(x, y, square, square, colorRGB(255,255,255));      
        // Hit - Red
        if(board[i] == 4) drawBox(x, y, square, square, colorRGB(255,0,0));      
        // Ship - Grey
        if(board[i] > 7 && yourBoard) drawBox(x, y, square, square, colorRGB(128,128,128));      
    
        x += square + 1;  // Leave a one pixel boarder between squares
    }
}

