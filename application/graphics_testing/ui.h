#ifndef UI_H
#define UI_H 1

#define MENU_OK 0;
#define MENU_ESCAPE -1;

/**
 * Create a menu and hand program control to it until the user
 * has selected a menu option. The value returned corresponds to
 * which menu item was selected. option1 returns 1. option2 returns 2 ...
 *
 * @param title Menu title to display
 * @param arrangement How the options should be listed in the menu
 * @param numOptions How many options to display
 * @param ... Selectable menu options
 */
int displayMenu(const char *title, unsigned int numOptions, ... );

/**
 * Display the board passed in based on the yourBoard bit. If displaying
 * yourBoard, the offest will be set to the top left of the screen and 
 * if displaying your opponents board (!yourBoard) the offest will display
 * the board in the bottom right corner. The boards will be displayed with 
 * blue for water, grey for ships, white for a miss, and red for a hit. 
 *
 *  ___________________
 *  |     |
 *  |your |
 *  |board|
 *  |_____|___________
 *  |     | 
 *  |     | opponents
 *  |     |   board
 *
 *
 * @param board[] Array of all water, ship, hit, and miss locations
 * @param yourBoard  1-display ships in the board, 0-do not show the ships
 */
void displayBoard(int board[], int yourBoard);

#endif //UI_H

