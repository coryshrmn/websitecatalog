/*
 * MenuManager.c
 * contains functions for handling menus
 *
 * Developer:       Gon Kim (imgonkim@gmail.com)
 * Initial Commit:  03172013_032604
 * Last Updated:    03182013_101952
 *
 */

#include "../header/WebsiteCatalog.h"
#include "../header/MenuManager.h"

/*
 *  MenuManager
 *  drives menu options
 *
 *  PRE:        head (list head)
 *              fPtr (file pointer)
 *              sFileName (safe file name)
 *
 *  POST:       prompts user menu
 *              && get menu option
 *
 *  RETURN:     none
 *
 */
void MenuManager(ListHead *head, FILE* fPtr, char* sFileName,
                 bool *isDataModified) {
	menu_type menu = MENU_TYPE_INVALID; // init: menu type
    
	menu = _getMenuSelection();
    //DEBUG
    printf("menu = %d\n", menu);
    fflush(stdout);
	switch (menu) {
        case MENU_TYPE_INVALID:
            printf(ERR_INVALID_MENU);
            break;
        case MENU_TYPE_ADD_DATA:
            _addDataFromMenu(head);
            *isDataModified = true;
            break;
        case MENU_TYPE_DELETE_DATA:
            _deleteDataFromMenu(head);
            *isDataModified = true;
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
            fPtr = _saveFromMenu(head, fPtr, sFileName, *isDataModified);
            if (!fPtr) {
                printf(ERR_COULD_NOT_REOPEN_FILE(sFileName, FILEMODE_OVERWRITE));
            }
            break;
        case MENU_TYPE_SAVE_AS:
            _saveAsFromMenu(head, &fPtr, &sFileName);
            break;
        case MENU_TYPE_QUIT:
            if (_quitFromMenu(head, fPtr, sFileName, *isDataModified)) {
                printf(VERB_QUIT_FROM_MENU);
            }
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
	sMenuSelection = _promptMenu();
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
	for (i = MENU_TYPE_ADD_DATA; i <= MENU_TYPE_QUIT; i++) {
		printf("%d.  %s\n", i, menu_msg[i]);
	}
	printf(HR);
    
	return;
}

/*
 *  _promptMenu
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
static menu_type _promptMenu(void) {
	int sInput; // safe user-input
    
	do {
		sInput = promptUserSelection(INPUT_TYPE_MENU,
                                     MSG_PROMPT_MENU_SELECTION);
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
	char *sUrl; // safe Url
	bool isDeleted = false; // is Url successfully deleted from the list
    
	sUrl = promptSingleField(INPUT_TYPE_URL, MSG_PROMPT_URL);
	isDeleted = listRemove(head, sUrl);
	isDeleted ?
    printf(VERB_LIST_DELETE(sUrl)) : printf(WARN_KEY_NOT_FOUND(sUrl));
	free(sUrl);
    
	return isDeleted;
}

static bool _findKeyFromMenu(ListHead *head) {
	char *sUrl; // safe url
	Website *pFound = NULL;
    
	sUrl = promptSingleField(INPUT_TYPE_URL, MSG_PROMPT_URL);
	if ((pFound = hashSearch(head, sUrl))) {
		websitePrintFull(pFound);
	}
	pFound ? printf(VERB_LIST_FOUND(sUrl)) : printf(WARN_KEY_NOT_FOUND(sUrl));
	free(sUrl);
    
	return pFound ? true : false;
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

static FILE* _saveFromMenu(ListHead *head, FILE *fPtr, char* sFileName,
                           bool isDataModified) {
	input_value saveOrNot = INPUT_VALUE_INVALID; // save option toggle
    
	if (isDataModified) {
		saveOrNot = promptUserSelection(INPUT_TYPE_SAVE, MSG_PROMPT_TO_SAVE);
		if (INPUT_VALUE_YES == saveOrNot) {
			fPtr = reopenCurrentFileStream(sFileName, FILEMODE_OVERWRITE, fPtr);
		}
        
		// TODO:
		// write: data to file
        
	} else {
		printf(VERB_DATA_NOT_MODIFIED(sFileName));
	}
    
	return fPtr;
}

static void _saveAsFromMenu(ListHead *head, FILE** fPtr, char **sFileName) {
    
	// fclose: if current session exists
	if (*fPtr) {
		if (!(closeFile(*fPtr, *sFileName))) { // if failed to close file
			printf(ERR_COULD_NOT_CLOSE_FILE(*sFileName));
			free(*sFileName);
			exit(EXIT_FILE_NOT_CLOSED);
		}
	}
    
	// fopen: new session in overwrite mode
	*sFileName = promptFileName(MSG_PROMPT_TO_SAVE_AS);
	*fPtr = fopen(*sFileName, FILEMODE_OVERWRITE);
	if (!(*fPtr)) {
		printf(ERR_COULD_NOT_OPEN_FILE(*sFileName));
		free(*sFileName);
		exit(EXIT_FILE_NOT_WRITTEN);
	}
    
	// TODO:
	// write: data to file
}

static bool _quitFromMenu(ListHead *head, FILE* fPtr, char *sFileName,
                          bool isDataModified) {
	input_value quitOrNot = INPUT_VALUE_INVALID;  // save option toggle
    
	// wish to quit program?
	if (INPUT_VALUE_YES
        == promptUserSelection(INPUT_VALUE_QUIT, MSG_PROMPT_QUIT)) {
		quitOrNot = INPUT_VALUE_YES;
        
		if (isDataModified) {
			// save session?
			if (INPUT_VALUE_YES == promptUserSelection(INPUT_TYPE_SAVE_AS,
                                       MSG_PROMPT_TO_SAVE_AS)) {
                    _saveAsFromMenu(head, &fPtr, &sFileName);
                }
			// TODO:
			// write: data to file
		} else {
			printf(VERB_DATA_NOT_MODIFIED(sFileName));
		}
	} else {
		quitOrNot = INPUT_VALUE_NO;
	}
	return INPUT_VALUE_YES == quitOrNot ? true : false;
}
