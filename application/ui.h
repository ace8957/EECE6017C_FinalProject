#ifndef UI_H
#define UI_H 1

const int MENU_OK = 0;
const int MENU_ESCAPE = -1;

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

#endif //UI_H
