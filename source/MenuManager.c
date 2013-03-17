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

menu_type getMenuSelection(void) {
	menu_type sMenuSelection; // safe menu selection
	
    _printMenu();
	sMenuSelection = _chooseMenu();
	return sMenuSelection;
}

/*
 * printMenu: This function prints menu options.
 *
 *  PRE:    none
 *  POST:   prints menu options
 *  RETURN: none
 *
 */
static void _printMenu() {
	int i;
    
	printf(HR);
	for (i = MENU_TYPE_ADD_DATA; i <= MENU_TYPE_SAVE_AND_QUIT; i++) {
		printf("%d.  %s\n", i, menu_msg[i]);
	}
	printf(HR);
    
	return;
}

/*  chooseMenu: This function prompts user to input menu selection
 *              from his or her keyboard and returns validated .
 *
 *  PRE:    none
 *  POST:   prompts user to input menu selection
 *  RETURN: sInput // safe user-input for menu selection
 *
 */
static menu_type _chooseMenu(void) {
	int sInput; // safe user-input
    
	do {
        sInput = getUserSelection(INPUT_TYPE_MENU, MSG_PROMPT_MENU_SELECTION);
	} while (INPUT_VALUE_INVALID == sInput ? printf(ERR_INVALID_INPUT) : 0);
	return sInput;
}