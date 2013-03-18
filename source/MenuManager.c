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


void MenuManager (ListHead *head, FILE* fPtr) {
    
    menu_type menu = MENU_TYPE_INVALID; // init: menu type

    menu = _getMenuSelection();
    switch (menu) {
        case MENU_TYPE_INVALID:
            printf(ERR_INVALID_MENU);
            break;
        case MENU_TYPE_ADD_DATA:
            _addDataFromMenu(head);
            break;
        case MENU_TYPE_DELETE_DATA:
            _deleteDataFromMenu(head);
           break; 
        case MENU_TYPE_FIND_KEY:
            _findKeyFromMenu(head);
            break;
        case MENU_TYPE_PRINT_HASH:
            _printHashFromMenu(head);
            break;
        case MENU_TYPE_PRINT_SORTED_SEQUENCE:
            _printSortedSequenceFromMenu(head);
            break;
        case MENU_TYPE_PRINT_INDENTED_TREE:
            _printIndentedTreeFromMenu(head);
            break;
        case MENU_TYPE_SAVE:
            _saveSessionFromMenu(head, fPtr);
            break;
        case MENU_TYPE_PRINT_EFFICIENCY:
            _printEfficiencyFromMenu(head);
            break;
        case MENU_TYPE_SAVE_AND_QUIT:
            _saveAndQuitFromMenu(fPtr);
            break;
    }
}


/*
 *  _getMenuSelection
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
static menu_type _getMenuSelection(void) {
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


// TODO: merge with SingleWebsiteManager.getSingleWebiste
static bool _addDataFromMenu(ListHead *head) {
    Website* curWebsite = NULL; // current `struct Website`
    char *sUrl = NULL;              // safe url
	char *sCompany = NULL;          // safe company name
	int sDailyPageView = 0;     // safe daily page view
	int sRankTraffic = 0;      // safe traffic rank
	int sBackLink = 0;         // safe backlink
	int sWebsiteWorth = 0;     // safe website worth
    /*
	 * `char *sInt;`
	 * safe int value
	 */
    char *sInt = NULL;

	// set: fields in `curWebsite`
	sUrl = (char*) promptSingleField(INPUT_TYPE_URL, MSG_PROMPT_URL);
	sCompany = (char*) promptSingleField(INPUT_TYPE_URL, MSG_PROMPT_COMPANY);
	sInt = (char*) promptSingleField(INPUT_TYPE_URL, MSG_PROMPT_DAILY_PAGE_VIEW);
    sDailyPageView = atoi(sInt);
	sInt = (char*) promptSingleField(INPUT_TYPE_URL, MSG_PROMPT_RANK_TRAFFIC);
	sRankTraffic = atoi(sInt);
	sInt = (char*) promptSingleField(INPUT_TYPE_URL, MSG_PROMPT_MENU_BACK_LINK);
	sBackLink = atoi(sInt);
	sInt = (char*) promptSingleField(INPUT_TYPE_URL, MSG_PROMPT_MENU_WEBSITE_WORTH);
	sWebsiteWorth = atoi(sInt);
    // convert: string to int




    
    curWebsite = websiteCreate(sUrl, sCompany, sDailyPageView, sRankTraffic, sBackLink, sWebsiteWorth);
    
    return NULL != curWebsite ? true : false;
}

static bool _deleteDataFromMenu(ListHead *head) {
}

static bool _findKeyFromMenu(ListHead *head) {
}

static bool _printHashFromMenu(ListHead *head) {
}

static bool _printSortedSequenceFromMenu(ListHead *head) {
}

static bool _printIndentedTreeFromMenu(ListHead *head) {
}

static bool _saveSessionFromMenu(ListHead *head, FILE *fPtr) {
}

static bool _printEfficiencyFromMenu(ListHead *head) {
}

static bool _saveAndQuitFromMenu(FILE *fPtr) {
}


