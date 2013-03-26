/*******************************************************************************
 * MenuManager.c
 * MenuManager handles the menu of the program
 *
 * Developer(s):
 * 		Gon Kim			(imgonkim@gmail.com)
 * 		Cory Sherman	(coryshrmn@gmail.com)
 *
 ******************************************************************************/
#include "WebsiteCatalog.h"
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH_MENU 10

// project.main.CONSTANT_DEFINED.error
#define ERR_INVALID_MENU            ">>>ERROR : Invalid menu option chosen. Please enter valid range (1-10).\n"
// project.main.CONSTANT_DEFINED.warning
#define WARN_ID_NOT_FOUND(type)     ">>WARNING: %s is not found.\n", type
#define WARN_URL_FOUND(url)         ">>WARNING: %s already exits in the list.\n", url
// project.main.CONSTANT_DEFINED.verbose
#define VERB_DATA_NOT_MODIFIED      ">VERBOSE : No changes has been made. Nothing had been written to the file.\n"
#define VERB_QUIT_FROM_MENU         ">VERBOSE : Exiting program from menu..\n"
#define VERB_ID_REMOVED(id)         ">VERBOSE : \"%s\" has been removed from the list.\n", id
#define VERB_AUTOSAVE(name)         ">VERBOSE : Autosaved to \"%s\"\n", name
#define VERB_FILE_WRITTEN(name)     ">VERBOSE : Data has been written to \"%s\".\n", name
// project.main.CONSTANT_DEFINED.message
#define MSG_PROMPT_URL              "Enter Url: "
#define MSG_PROMPT_COMPANY          "Enter Company Name: "
#define MSG_PROMPT_DAILY_VIEW       "Enter Daily Page View: "
#define MSG_PROMPT_RANK_TRAFFIC     "Enter Traffic Rank: "
#define MSG_PROMPT_BACK_LINK        "Enter Back Link: "
#define MSG_PROMPT_WEBSITE_WORTH    "Enter Website Worth: "
#define MSG_PROMPT_MENU             "Enter your option (1-10): "

// project.main.CONSTANT_STRING
const char *MENU_MESSAGE[MAX_LENGTH_MENU] = { "1 - Insert a Website\n",
		"2 - Delete a Website by URL\n", "3 - Search for a Website by URL\n",
		"4 - Print hash buckets\n", "5 - Print BST in order\n",
		"6 - Print BST indented\n", "7 - Print hash efficiency\n", "8 - Save\n",
		"9 - Save as...\n", "10 - Quit\n" };

/*******************************************************************************
 * 
 * MenuManager private prototypes
 *
 ******************************************************************************/
MENU_OPTION _promptMenu(void);
static void _printMenu(void);
static void _insertFromMenu(ListHead *head, bool *isDataModified);
static void _deleteFromMenu(ListHead *head, bool *isDataModified);
static void _searchFromMenu(ListHead *head);
static void _printHashFromMenu(ListHead *head);
static void _printInorderFromMenu(ListHead *head);
static void _printIndentedFromMenu(ListHead *head);
static void _printEfficiencyFromMenu(ListHead *head);
static void _saveFromMenu(ListHead *head, char* sfName, bool *isDataModified);
static void _saveAsFromMenu(ListHead *head, char** sfName, bool *isDataModified);
static void _quitFromMenu(ListHead *head, char *sFileName, bool isDataModified);

/*******************************************************************************
 * Drives menu.
 *
 *    Pre: head is the header of the list
 *		  sfName is the safe fiel name
 *
 *   Post: Prompts menu option and processes menu
 *
 * Return: none
 ******************************************************************************/
void MenuDriver(ListHead *head, char* sfName) {
	MENU_OPTION menuChoice; // init: menu type
	bool isDataModified = false;

	do {
		menuChoice = _promptMenu();
		switch (menuChoice) {
		case MENU_INSERT:
			_insertFromMenu(head, &isDataModified);
			break;
		case MENU_DELETE:
			_deleteFromMenu(head, &isDataModified);
			break;
		case MENU_SEARCH:
			_searchFromMenu(head);
			break;
		case MENU_PRINT_HASH:
			_printHashFromMenu(head);
			break;
		case MENU_PRINT_INORDER:
			_printInorderFromMenu(head);
			break;
		case MENU_PRINT_INDENTED:
			_printIndentedFromMenu(head);
			break;
		case MENU_PRINT_EFFICIENCY:
			_printEfficiencyFromMenu(head);
			break;
		case MENU_SAVE:
			_saveFromMenu(head, sfName, &isDataModified);
			break;
		case MENU_SAVE_AS:
			_saveAsFromMenu(head, &sfName, &isDataModified);
			break;
		case MENU_QUIT:
			_quitFromMenu(head, sfName, isDataModified);
			break;
		default:
			printf(ERR_INVALID_MENU);
			return;
			break;
		}
	} while (menuChoice != MENU_QUIT);
}
/*******************************************************************************
 * Prints menu options.
 *
 *    Pre: none
 *		  
 *
 *   Post: Prints menu options.
 *         
 *
 * Return: none.
 ******************************************************************************/
static void _printMenu(void) {
	int i;

	printf(HR);
	for (i = MENU_INSERT; i <= MENU_QUIT; i++) {
		printf("%d.  %s\n", i, MENU_MESSAGE[i]);
	}
	printf(HR);

	return;
}
/*******************************************************************************
 * Prompts user to add Website info by Url.
 *
 *    Pre: head is the header of the list		  
 *
 *   Post: prompt user to add Website info.
 *         
 * Return: true if successfully inserted
 *        false if failed.
 ******************************************************************************/
static void _insertFromMenu(ListHead *head, bool *isDataModified) {
	char *sUrl = NULL;          // safe url
	char *sCompany = NULL;      // safe company name
	char *buff;					// buffer for userinput
	Website tempWebsite;	// temporary website struct to check if Url exists
	Website *pCreate;			// temporary website struct to be inserted

	// insert: url
	sUrl = promptInput(INPUT_TYPE_URL, MSG_PROMPT_URL);
	strcpyToLower(sUrl, sUrl);
	tempWebsite.url = sUrl;
	if (!hashInsert(head, &tempWebsite)) {
		free(sUrl);
		return;
	}
	hashRemove(head, sUrl);
	pCreate = malloc(sizeof(Website));
	pCreate->url = sUrl;

	// insert: company name
	sCompany = promptInput(INPUT_TYPE_COMPANY, MSG_PROMPT_COMPANY);
	pCreate->company = sCompany;

	// insert: daily page view
	buff = promptInput(INPUT_TYPE_DAILY_PAGE_VIEW, MSG_PROMPT_DAILY_VIEW);
	pCreate->dailyPageViewThousands = atoi(buff);
	free(buff);

	// insert: daily page view
	buff = promptInput(INPUT_TYPE_RANK_TRAFFIC, MSG_PROMPT_RANK_TRAFFIC);
	pCreate->rankTraffic = atoi(buff);
	free(buff);
    
	// insert: back link
	buff = promptInput(INPUT_TYPE_BACK_LINK, MSG_PROMPT_BACK_LINK);
	pCreate->backLinkThousands = atoi(buff);
	free(buff);

	// insert: website worth
	buff = promptInput(INPUT_TYPE_WEBSITE_WORTH, MSG_PROMPT_WEBSITE_WORTH);
	pCreate->websiteWorthThousands = atoi(buff);
	free(buff);

	if (listInsert(head, pCreate)) {
		*isDataModified = true;
	}
}
/*******************************************************************************
 * Deletes data with Url if found from the list.
 *
 *    Pre: head is the header of the list
 *		   isDataModified is the tracker for data changes.
 *
 *   Post: Prompts user to enter the Url to be deleted.
 *         Validates the Url.
 *         Deletes from the list.
 *
 * Return: none
 ******************************************************************************/

static void _deleteFromMenu(ListHead *head, bool *isDataModified) {
	bool valid;
	char *sUrl;

	valid = false;
	sUrl = promptInput(INPUT_TYPE_URL, MSG_PROMPT_URL);
	strcpyToLower(sUrl, sUrl);
	validateInput(INPUT_TYPE_URL, sUrl);

	if (listRemove(head, sUrl)) {
		printf(VERB_ID_REMOVED(sUrl));
		*isDataModified = true;
	} else {
		printf(WARN_ID_NOT_FOUND(sUrl));
	}

	free(sUrl);
}
/*******************************************************************************
 * Searches the node with Url.
 *
 *    Pre: head is the header of the list
 *
 *   Post: Prompts user to enter the Url to be deleted.
 *         Validates the Url.
 *         Searches the node with the Url.
 *
 * Return: none
 ******************************************************************************/

static void _searchFromMenu(ListHead *head) {
	bool valid;
	char *sUrl;
	Website *pFound;
	valid = false;

	sUrl = promptInput(INPUT_TYPE_URL, MSG_PROMPT_URL);
	strcpyToLower(sUrl, sUrl);
	pFound = hashSearch(head, sUrl);
	if (pFound) {
		websitePrintFull(pFound);
	} else {
		printf(WARN_ID_NOT_FOUND(sUrl));
	}
  free(sUrl);
}
/*******************************************************************************
 * Prints the hash bucket list.
 *
 *    Pre: head is the header of the list
 *		  
 *   Post: Prints the hash bucket list.
 *         
 * Return: none
 ******************************************************************************/

static void _printHashFromMenu(ListHead *head) {
	hashPrintList(head);
}
/*******************************************************************************
 * Prints inorder traversed BST tree
 *
 *    Pre: head is the header of the list
 *
 *   Post: Prints inorder traversed BST tree
 *
 * Return: none
 ******************************************************************************/

static void _printInorderFromMenu(ListHead *head) {
	bstPrintInorder(head);
}
/*******************************************************************************
 * Prints indented BST tree.
 *
 *    Pre: head is the header of the list
 *		  
 *   Post: Prints indented BST tree.
 *         
 *
 * Return: none
 ******************************************************************************/

static void _printIndentedFromMenu(ListHead *head) {
	bstPrintIndented(head);
}
/*******************************************************************************
 * Prints efficiency table.
 *
 *    Pre: head is the header of the list
 *		  
 *   Post: Prints efficiency table.
 *         
 * Return: none
 ******************************************************************************/

static void _printEfficiencyFromMenu(ListHead *head) {
	printEfficiency(head);
}
/*******************************************************************************
 * Saves the changed into the current file.
 *
 *    Pre: head is the header of the list
 *		  
 *   Post: If data is modified, the data is written to current file.
 *		   If data is not modified, the data is not written.
 *         
 * Return: none
 ******************************************************************************/

static void _saveFromMenu(ListHead *head, char* sfName, bool *isDataModified) {

	if (*isDataModified) {
		if (writeFile(sfName, bstTraverseBreadth(head))) {
			printf(VERB_FILE_WRITTEN(sfName));
			*isDataModified = false;
		} else {
			printf(ERR_FILE_NOT_WRITTEN(sfName));
			exit(EXIT_FILE_NOT_WRITTEN);
		}
	} else {
		printf(VERB_DATA_NOT_MODIFIED);
	}
}
/*******************************************************************************
 * Saves the changed data into a different file.
 *
 *    Pre: head is the header of the list
 *	 	  sfNAme is the currently opened filename
 *		  isDataModified is the tracker for data changes.
 *
 *   Post: Prompts user to enter the new file name.
 *		  Writes data to the entered file name.
 *         
 * Return: none
 ******************************************************************************/

static void _saveAsFromMenu(ListHead *head, char** sfName, bool *isDataModified) {
	char *sfNameNew;

	sfNameNew = promptInput(INPUT_TYPE_FILENAME, MSG_PROMPT_FILENAME);
	if (!strcmp(sfNameNew, *sfName)) {
		if (*isDataModified) {
			if (!writeFile(*sfName, bstTraverseBreadth(head))) {
				printf(ERR_FILE_NOT_WRITTEN(*sfName));
				exit(EXIT_FILE_NOT_WRITTEN);
			}
			printf(VERB_FILE_WRITTEN(*sfName));
			*isDataModified = false;
		} else {
			printf(VERB_DATA_NOT_MODIFIED);
		}
		free(sfNameNew);
	} else {
		if (!writeFile(sfNameNew, bstTraverseBreadth(head))) {
			printf(ERR_FILE_NOT_WRITTEN(sfNameNew));
			exit(EXIT_FILE_NOT_WRITTEN);
		}
		printf(VERB_FILE_WRITTEN(sfNameNew));
		*isDataModified = false;
		free(sfNameNew);
		*sfName = sfNameNew;
	}
}
/*******************************************************************************
 * Exits from the menu.
 *
 *    Pre: head is the header of the list
 *		  isDataModified is the tracker for data changes.
 *
 *   Post: If unsaved changes remain, the data is automatically saved to a backup file.
 *         Then, exits the menu
 *
 * Return: none
 ******************************************************************************/

static void _quitFromMenu(ListHead *head, char *sfName, bool isDataModified) {
	if (isDataModified) {
		sfName = appendBackupExtension(sfName);
		if (!writeFile(sfName, bstTraverseBreadth(head))) {
			printf(ERR_FILE_NOT_WRITTEN(sfName));
			exit(EXIT_FILE_NOT_WRITTEN);
		}
		printf(VERB_AUTOSAVE(sfName));
    free(sfName);
	}
}

/*******************************************************************************
 * Prints the menu to the user, and loops until they enter a valid choice.
 *
 *    Pre: none
 *
 *   Post: The user has chosen a valid option
 *
 * Return: The user's selected option
 ******************************************************************************/
MENU_OPTION _promptMenu(void) {
	int choice;
	char *sMenu;
	int i;

	printf(HR);
	for (i = 0; i < MAX_LENGTH_MENU; i++) {
		printf("%s", MENU_MESSAGE[i]);
	}
	printf(HR);

	sMenu = promptInput(INPUT_TYPE_MENU, MSG_PROMPT_MENU);
	choice = atoi(sMenu);

	free(sMenu);

	return choice;
}

