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

void MenuManager(ListHead *head, FILE* fPtr, char* sFileName) {
    
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
        case MENU_TYPE_PRINT_EFFICIENCY:
            _printEfficiencyFromMenu(head);
            break;
        case MENU_TYPE_SAVE:
            _saveFromMenu(head, fPtr, sFileName);
            break;
        case MENU_TYPE_SAVE_AS:
            _saveAsFromMenu(head);
            break;
        case MENU_TYPE_SAVE_AND_QUIT:
            fclose(fPtr);
            if (_quitFromMenu(head)) {
                printf(VERB_QUIT_FROM_MENU);
            } else {
                printf(ERR_UNABLE_TO_QUIT_FROM_MENU);
                exitOnUserRequest(EXIT_ON_USER_REQUEST);
            }
            
            break;
	}
    
    return;
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
		sInput = promptUserSelection(INPUT_TYPE_MENU, MSG_PROMPT_MENU_SELECTION);
	} while (INPUT_VALUE_INVALID == sInput ? printf(ERR_INVALID_INPUT) : 0);
	return sInput;
}

/*
 *  _addDataFromMenu
 *  prompts user to add Website info.
 *
 *  PRE:        head (list header)
 *
 *  POST:       prompt user to add Website info.
 *
 *  RETURN:     true if successfully inserted
 *              false if failed.
 *
 */
static bool _addDataFromMenu(ListHead *head) {
	Website* curWebsite = NULL; // current `struct Website`
	char *sUrl = NULL;          // safe url
	char *sCompany = NULL;      // safe company name
	int sDailyPageView = 0;     // safe daily page view
	int sRankTraffic = 0;       // safe traffic rank
	int sBackLink = 0;          // safe backlink
	int sWebsiteWorth = 0;      // safe website worth
	/*
	 * `char *sInt;`
	 * safe int value
	 */
	char *sInt = NULL;
    
	// set: fields in `curWebsite`
	sUrl = (char*) promptSingleField(INPUT_TYPE_URL, MSG_PROMPT_URL);
	sCompany = (char*) promptSingleField(INPUT_TYPE_COMPANY,
                                         MSG_PROMPT_COMPANY);
    
	sInt = (char*) promptSingleField(INPUT_TYPE_DAILY_PAGE_VIEW,
                                     MSG_PROMPT_DAILY_PAGE_VIEW);
	sDailyPageView = atoi(sInt);
	free(sInt);
    
	sInt = (char*) promptSingleField(INPUT_TYPE_RANK_TRAFFIC,
                                     MSG_PROMPT_RANK_TRAFFIC);
	sRankTraffic = atoi(sInt);
	free(sInt);
    
	sInt = (char*) promptSingleField(INPUT_TYPE_BACK_LINK,
                                     MSG_PROMPT_MENU_BACK_LINK);
	sBackLink = atoi(sInt);
	free(sInt);
    
	sInt = (char*) promptSingleField(INPUT_TYPE_WEBSITE_WORTH,
                                     MSG_PROMPT_MENU_WEBSITE_WORTH);
	sWebsiteWorth = atoi(sInt);
	free(sInt);
    
	curWebsite = websiteCreate(sUrl, sCompany, sDailyPageView, sRankTraffic,
                               sBackLink, sWebsiteWorth);
    
	free(sUrl);
	free(sCompany);
    
	return listInsert(head, curWebsite);
}
static bool _deleteDataFromMenu(ListHead *head) {
	char *url;
	url = promptSingleField(INPUT_TYPE_URL, MSG_PROMPT_URL);
	printf(listRemove(head, url) ? "Delete\n" : "Not found\n");
	free(url);
}

static bool _findKeyFromMenu(ListHead *head) {
	char *url;
	Website *pFound;
	url = promptSingleField(INPUT_TYPE_URL, MSG_PROMPT_URL);
	if (pFound = hashSearch(head, url))
		websitePrintFull(pFound);
	else
		printf("Not found\n");
	free(url);
}

static void _printHashFromMenu(ListHead *head) {
	hashPrintList(head);
}

static void _printSortedSequenceFromMenu(ListHead *head) {
	bstPrintInorder(head);
}

static void _printIndentedTreeFromMenu(ListHead *head) {
	bstPrintIndented(head);
}


static void _printEfficiencyFromMenu(ListHead *head) {
	printEfficiency(head);
}


static FILE* _saveFromMenu(ListHead *head, FILE *fPtr, char* sFileName) {
    input_value saveYesOrNo = INPUT_VALUE_INVALID; // save yes or no

    saveYesOrNo = promptUserSelection(INPUT_TYPE_SAVE, MSG_PROMPT_TO_SAVE);
    fPtr = reopenCurrentFileStream(sFileName, FILEMODE_OVERWRITE, fPtr);
    
}

static FILE *_saveAsFromMenu(ListHead *head) {
    FILE* fPtr = NULL; // file pointer
    char *sFileName = NULL; // safe file name
    
    sFileName = promptFileName(MSG_PROMPT_TO_SAVE_AS);
    fPtr = fopen(sFileName, FILEMODE_OVERWRITE);
    if(!fPtr) {
        printf(ERR_NOT_SAVED);
        exit(EXIT_FILE_NOT_WRITTEN);
    }
    
    return fPtr;
}


static bool _quitFromMenu(ListHead *head) {
    input_value saveYesOrNo = INPUT_VALUE_INVALID; // save yes or no
    FILE *fPtr = NULL; // file pointer
    char *sFileName = NULL; // safe file name
    
    // save session?
    saveYesOrNo = promptUserSelection(INPUT_TYPE_SAVE, MSG_PROMPT_TO_SAVE);
    if (INPUT_VALUE_YES == saveYesOrNo) {
        sFileName = promptFileName(MSG_PROMPT_TO_SAVE_AS);
        fPtr = fopen(sFileName, FILEMODE_OVERWRITE);
        if (!fPtr) {
            printf(ERR_NOT_SAVED);
            exit(EXIT_FILE_NOT_WRITTEN);
        }
        fclose(fPtr);
    }
    
    
}