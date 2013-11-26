#include "ui.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "graphics.h"
#include "keyboard.h"

int displayMenu(const char *title, unsigned int numOptions, ...)
{
    int selection = 1;
    va_list options;
    // Get the options
    char optionList[16][256];
    unsigned int i;
    va_start(options, numOptions);
    for(i = 0; i < numOptions; ++i) {
        char *option = va_arg(options, char*);
        strncpy(optionList[i], option, 256);
    }
    va_end(options);

    // Draw the menu background in dark gray
    drawBox(0, 0, VGA_WIDTH, VGA_HEIGHT, colorRGB(30, 30, 30));

    // Calculate the outermost menubox width and height
    const int optionBoxHeight = 10,
              optionBoxSeparation = 4,
              optionBoxWidth = 150;
    int menuWidth = 200;
    int menuHeight = (numOptions+1)*(optionBoxHeight+optionBoxSeparation);

    int menuX = (VGA_WIDTH-menuWidth)/2;
    int menuY = (VGA_HEIGHT-menuHeight)/2;

    drawBox(menuX, menuY, menuWidth, menuHeight, colorRGB(11, 10, 177));
    
    // Draw the title
    drawText(menuX+10, menuY+10, title);
   
    // User wants to display a message box
    if(numOptions == 0) {
        strncpy(optionList[0], "Okay", 256);
        numOptions = 1;
    }

    int keyPress;
    int optionX = (menuX+menuWidth-optionBoxWidth)/2,
        optionY;
    do {
        // Draw the selection background
        optionY = menuY+selection*optionBoxHeight - (optionBoxSeparation/2);
        drawBox(optionX, optionY, optionBoxWidth, optionBoxHeight+optionBoxSeparation, colorRGB(50, 50, 110));

        // Draw the options in their own boxes, with the first option highlighted
        for(i = 0; i < numOptions; ++i) {
            optionY = menuY+selection*optionBoxHeight;
            drawBox(optionX, optionY, optionBoxWidth, optionBoxHeight, colorRGB(80, 80, 110));
            drawText(optionX+10, optionY+(optionBoxHeight/2), optionList[i]);
        }

        keyPress = getKey();
        if(keyPress == ESC) {
            selection = MENU_ESCAPE;
            break;
        }
        else if(keyPress == ENTER) {
            break;
        }
        else if(keyPress == UP) {
            selection = (selection + 1)%numOptions;
        }
        else if(keyPress == DOWN) {
            --selection;
            if(selection == 0)
                selection = numOptions;
        }
        // ignore other keys, no other options

    }
    while(1);

    return selection;
}


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
        if(board[i] == 0) drawBox(x, y, square, square, COLOR_WATER);
        // Miss - White
        if(board[i] == 2) drawBox(x, y, square, square, COLOR_MISS);
        // Hit - Red
        if(board[i] == 4) drawBox(x, y, square, square, COLOR_HIT);
        // Ship - Grey
        if(board[i] > 7 && yourBoard) drawBox(x, y, square, square, COLOR_SHIP);
    
        x += square + 1;  // Leave a one pixel boarder between squares
    }
}
