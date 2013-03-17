/*
 * MenuManager.c
 * contains functions for handling menus
 *
 * Developer:       Gon Kim (imgonkim@gmail.com)
 * Initial Commit:  03172013_032604
 * Last Updated:    03172013_055555
 *
 */

#include "../header/WebsiteCatalog.h"
#include "../header/MenuManager.h"

/*
 *  getMenuSelection
 *  gets menu selection from user and returns
 *  validated menu type.
 *
 *  PRE:        none
 *
 *  POST:       prints menu
 *              && get menu option
 *
 *  RETURN:     sMenuSelection
 *
 */
menu_type getMenuSelection(void) {
	menu_type sMenuSelection; // safe menu selection
	
    _printMenu();
	sMenuSelection = _chooseMenu();
	return sMenuSelection;
}

/*
 *  _printMenu
 *  prints menu options.
 *
 *  PRE:        none
 *
 *  POST:       prints menu options
 *
 *  RETURN:     none
 *
 */
static void _printMenu(void) {
	int i;
    
	printf(HR);
	for (i = MENU_TYPE_ADD_DATA; i <= MENU_TYPE_SAVE_AND_QUIT; i++) {
		printf("%d.  %s\n", i, menu_msg[i]);
	}
	printf(HR);
    
	return;
}

/*
 *  _chooseMenu
 *  prompts user to enter menu selection from stdio
 *  and returns validated menu type.
 *
 *  PRE:        none
 *
 *  POST:       prompts user to get menu option
 *
 *  RETURN:     sInput (menu type; validated)
 *
 */
static menu_type _chooseMenu(void) {
	int sInput; // safe user-input
    
	do {
        sInput = getUserSelection(INPUT_TYPE_MENU, MSG_PROMPT_MENU_SELECTION);
	} while (INPUT_VALUE_INVALID == sInput ? printf(ERR_INVALID_INPUT) : 0);
	return sInput;
}