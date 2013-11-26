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
}
