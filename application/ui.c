#include "ui.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "graphics.h"
#include "keyboard.h"

/**
 * The text drawn by the drawText function is 8x8 pixels for every
 * character.
 *
 * ------------------------------------------------------------
 * |                         Title                            |
 * |    __________________________________________________    |
 * |   |__________________________________________________|   |
 * |   ||                  Option #1                     ||   |
 * |   |--------------------------------------------------|   |
 * |   ----------------------------------------------------   |
 * |    __________________________________________________    |
 * |    |                  Option #2                     |    |
 * |    --------------------------------------------------    |
 */
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

    // User wants to display a message box
    if(numOptions == 0) {
        strncpy(optionList[0], "Okay", 256);
        numOptions = 1;
    }

    // Draw the menu background in dark gray
    drawBox(0, 0, VGA_WIDTH, VGA_HEIGHT, colorRGB(30, 30, 30));

    // Calculate the outermost menubox width and height
    const int optionBoxHeight = 12,
              optionBoxSeparation = 4,
              optionBoxWidth = 150,
              charWidth = 8,
              charHeight = 8;
    int menuWidth = 200;
    int menuHeight = (numOptions+1)*(optionBoxHeight+optionBoxSeparation);

    int menuX = (VGA_WIDTH-menuWidth)/2;
    int menuY = (VGA_HEIGHT-menuHeight)/2;

    drawBox(menuX, menuY, menuWidth, menuHeight, colorRGB(11, 10, 177));
    
    // Draw the title
    int textLen = strlen(title)*charWidth;
    int optionX = menuX+(menuWidth-textLen)/2,
        optionY = menuY+(optionBoxHeight+optionBoxSeparation)/2;
    drawText(optionX, optionY, title);
   
    int keyPress;
    do {
        // Draw the selection background
        optionX = menuX+(menuWidth-optionBoxWidth)/2;
        optionY = menuY+selection*optionBoxHeight + (optionBoxSeparation/2);
        drawBox(optionX, optionY, optionBoxWidth+optionBoxSeparation, optionBoxHeight+optionBoxSeparation, colorRGB(50, 50, 110));

        optionX = menuX+(menuWidth-optionBoxWidth+optionBoxSeparation)/2;
        // Draw the options in their own boxes, with the first option highlighted
        for(i = 0; i < numOptions; ++i) {
            textLen = strlen(optionList[i])*charWidth;
            optionY = menuY+(i+1)*(optionBoxHeight+optionBoxSeparation/2);
            drawBox(optionX, optionY+(optionBoxSeparation/2), optionBoxWidth, optionBoxHeight, colorRGB(80, 80, 110));
            drawText(optionX+(optionBoxWidth-textLen)/2, optionY+(optionBoxHeight), optionList[i]);
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
    int top = 0;
    int left = 0;
    int textWidthSpace = 10;
    const char *rows[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    const char *cols[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    if(yourBoard){
        x = left = 1;
        y = top = 1;
    } else {
        x = left = dimension + 3*textWidthSpace + 1;
        y = top = dimension - 60 + 1;
        dimension = 160;
    }  
    
    drawBox(x, y, dimension, dimension, colorRGB(0,0,0));
    // Set the dimension for each individual square (12 or 16 pixels)
    int square = dimension/10;

    // If you are drawing their board, write the row and column titles
    // Loop through the board array and color individual squares accordingly
    int i = 0;
    for(i = 0; i<100; ++i){
        // Reset x & y coordinates for a new row
        if(i%10 == 0){
            if(i > 9) {
                x = left;
                y += square + 2;
            }
            if(!yourBoard)
                drawText(x-textWidthSpace, y+textWidthSpace+textWidthSpace/4, rows[i/10]);
        }
        if(i <= 9 && !yourBoard) {
           drawText(x+textWidthSpace/2, y-textWidthSpace, cols[i]); 
        }

        // Water - Red
        if(board[i] == 0) drawBox(x, y, square, square, COLOR_WATER);
        // Miss - White
        if(board[i] == 2) drawBox(x, y, square, square, COLOR_MISS);
        // Hit - Red
        if(board[i] == 4) drawBox(x, y, square, square, COLOR_HIT);
        // Ship - Grey
        if(board[i] > 7 && yourBoard) drawBox(x, y, square, square, COLOR_SHIP);
        else if(board[i] > 7) drawBox(x, y, square, square, COLOR_WATER);
    
        x += square + 1;  // Leave a one pixel boarder between squares
    }
}
