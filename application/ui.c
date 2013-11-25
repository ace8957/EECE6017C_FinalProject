#include "ui.h"
#include <stdarg.h>
#include "graphics.h"
#include "keyboard.h"

int displayMenu(const char *title, unsigned int numOptions, ...)
{
    int selection = 1;
    // Some how store the colors in the area the menu will take?

    char optionList[10][256];
    va_list options;
    va_start(&options, numOptions);
    for(int i = 0; i < numOptions; ++i) {
        
    }
    // Draw the menu background
    
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
