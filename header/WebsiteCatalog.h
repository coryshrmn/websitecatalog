/*******************************************************************************
 * WebsiteCatalog.h
 *
 * Developer(s):
 * 		Cory Sherman	(coryshrmn@gmail.com)
 * 		Gon Kim			(imgonkim@gmail.com)
 *		Chris Huang		(christopher.e.huang@gmail.com)
 *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "queueADT.h"
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

// project.main.CONSTANT_DEFINED.formatting
#define HR  "================================================\n"
#define BR                                      "\n"

// project.main.CONSTANT_DEFINED.exitcode
#define EXIT_NOT_ENOUGH_MEMORY                  101
#define EXIT_FILE_NOT_OPENED                    102
#define EXIT_FILE_NOT_CLOSED                    103
#define EXIT_FILE_NOT_WRITTEN                   104
#define EXIT_ON_USER_REQUEST                    105
// project.main.CONSTANT_DEFINED.delimiter
#define DELIMITER_SPACE                         ' '
#define DELIMITER_SEMICOLON                     ';'
#define DELIMITER_NEWLINE                       '\n'
#define DELIMITER_SLASH                         '/'
#define DELIMITER_DOT                           '.'
#define DELIMITER_ZERO                          '0'
#define DELIMITER_UNDERSCORE                    '_'
#define DELIMITER_DASH                          '-'
// project.main.CONSTANT_DEFINED.fileio
#define FILEMODE_READONLY                       "r"
#define FILEMODE_WRITE                          "w"
#define FILEMODE_OVERWRITE                      "w+"
#define MAX_LENGTH_INPUT                        255
#define MAX_LENGTH_FILENAME                     MAX_LENGTH_INPUT
#define FLUSH while (getchar() != '\n');
#define USERINPUT_QUIT                          "QUIT"
// project.main.CONSTANT_DEFINED.error
#define ERR_COULD_NOT_CLOSE_FILE(name)          ">>>ERROR : Could not close file \"%s\".\n", name
#define ERR_COULD_NOT_OPEN_FILE(name)           ">>>ERROR : Could not open file, \"%s\".\n", name
#define ERR_COULD_NOT_REOPEN_FILE(name, mode)   ">>>ERROR : Could not re-open file \"%s\" with \"%s\" mode.\n", name, mode
#define ERR_NOT_ENOUGH_MEMORY                   ">>>ERROR : Not enough memory.\n"
#define ERR_INVALID_INPUT                       ">>>ERROR : Invalid input. Please try again.\n"
#define ERR_FILE_NOT_WRITTEN(name)              ">>>ERROR: Data could not be written to \"%s\".\n", name
// project.main.CONSTANT_DEFINED.verbose
#define VERB_EXIT_ON_USER_REQUEST               ">VERBOSE : Exiting program on user request"
#define VERB_EXIT_NORMALLY                      ">VERBOSE : Exiting program normally."
// project.main.CONSTANT_DEFINED.message
#define MSG_PROMPT_RECONFIRM                    "Are you sure?\n"
#define MSG_PROMPT_FILENAME                     "Please enter the filename: "
#define MSG_EXIT_SELECTION                      "Enter \"I\" to ignore once, \
\"A\" to ignore all,         \
or \"Q\" to quit program\n"


typedef enum {
	INPUT_VALUE_INVALID = -1, /* -1 */
	INPUT_VALUE_NO, /*  0 */
	INPUT_VALUE_YES, /*  1 */
	INPUT_VALUE_VALID, /*  2 */
	INPUT_VALUE_IGNORE, /*  3 */
	INPUT_VALUE_IGNORE_ALL, /*  4 */
	INPUT_VALUE_QUIT /*  5 */
} input_value;


typedef enum {
	INPUT_TYPE_URL = 2001, /* 2001 */
	INPUT_TYPE_COMPANY, /* 2002 */
	INPUT_TYPE_DAILY_PAGE_VIEW, /* 2003 */
	INPUT_TYPE_RANK_TRAFFIC, /* 2004 */
	INPUT_TYPE_BACK_LINK, /* 2005 */
	INPUT_TYPE_WEBSITE_WORTH, /* 2006 */
    
	INPUT_TYPE_FILENAME = 3001, /* 3001 */
	INPUT_TYPE_EXIT_ON_INVALID_FIELD, /* 3002 */
	INPUT_TYPE_RECONFIRM, /* 3003 */
	INPUT_TYPE_DISCARD, /* 3004 */
	INPUT_TYPE_SAVE, /* 3005 */
	INPUT_TYPE_SAVE_AS, /* 3006 */
	INPUT_TYPE_QUIT, /* 3007 */
    
	INPUT_TYPE_MENU = 4001 /* 4001 */
} input_type;

typedef struct
{
    char *url;  //primary key
    char *company;
    int dailyPageViewThousands;
    int rankTraffic;
    int backLinkThousands;
    int websiteWorthThousands;
} Website;

typedef struct _hashNode
{
    char *key;
    Website *site;
} HashNode;

typedef struct _bstNode
{
    struct _bstNode *left;
    char *key;
    Website *site;
    struct _bstNode *right;
} BstNode;

typedef struct
{
    int count;
    int arySize;
    int bucketSize;  // always 3
    HashNode *pHash; // array length bucketSize * arySize
    BstNode *pTree;
} ListHead;

typedef enum {false, true} bool;

/*******************************************************************************
 * Utility prototypes
 ******************************************************************************/

/*******************************************************************************
 * Trims the end of a c-string by padding it with '\0'.
 *
 *    Pre: string is a valid c-string
 *
 *   Post: all non graphical characters at the end of the string are replaced
 *         with '\0'
 *
 * Return: --
 ******************************************************************************/
void trimEnd(char *string);

/*******************************************************************************
 * Validates the pointer is not NULL.
 * If pointer is NULL, exit(EXIT_FAILURE) is called.
 *
 *    Pre: pointer is the pointer to test
 *
 *   Post: pointer is not NULL, or exit(EXIT_FAILURE) is called.
 *
 * Return: pointer
 ******************************************************************************/
void *validate(void *pointer);

/*******************************************************************************
 * Prints an integer with commas every 3 digits. Not padded.
 *
 *    Pre: val is the value to print
 *
 *   Post: val is printed to the screen, with commas every 3 digits.
 *
 * Return: --
 ******************************************************************************/
void printIntCommas(int val);


/*******************************************************************************
 * InsertManager prototypes
 ******************************************************************************/

/*******************************************************************************
 * Attempts to insert a Website into a hash table and BST.
 *
 *    Pre: pList points to a list with a hash table and BST.
 *         pWebsite is initialized.
 *
 *   Post: The Website has been inserted or destroyed.
 *
 * Return: true iff the Website was successfully inserted.
 ******************************************************************************/
bool listInsert(ListHead *pList, Website *pWebsite);

/*******************************************************************************
 * Attempts to remove a Website from a hash table and BST.
 *
 *    Pre: pList points to a list with a hash table and BST.
 *         url is the url of the Website to remove.
 *
 *   Post: The hash table and BST do not contain a website with that URL.
 *         If they did, it has been destroyed.
 *
 * Return: true if the Website was successfully removed,
 *         false if it was not found.
 ******************************************************************************/
bool listRemove(ListHead *pList, const char *url);

/*******************************************************************************
 * HashManager prototypes
 ******************************************************************************/

/*******************************************************************************
 * Creates a hashtable for the specified ListHead
 *
 *    Pre: pList points to a list with no hashtable.
 *         pList->bucketSize is initialized.
 *         numLines is not negative.
 *
 *   Post: The hashtable has been created and is pointed to by pList->pHash.
 *         Its length is the first prime number at least numLines * 2
 *         Its length is stored to pList->aryLength;
 *
 * Return: --
 ******************************************************************************/
void hashCreate(ListHead *pList, int numLines);

/*******************************************************************************
 * Attempts to insert Website into a hashtable.
 *
 *    Pre: pList points to a list which is initialized and has a valid hashtable.
 *         pWebsite points to a valid website.
 *
 *   Post: If the hashtable has room for the website and does not contain
 *         an entry with the same URL, it is inserted.
 *         Otherwise, a warning is printed to the screen and the pointer is discarded.
 *
 * Return: true if the website was successfully inserted.
 *         false if the hashtable already contained an entry for the url,
 *               or if the bucket was full.
 ******************************************************************************/
bool hashInsert(ListHead *pList, Website *pWebsite);

/*******************************************************************************
 * Searches a hashtable for the specified url.
 *
 *    Pre: pList points to a list which is initialized and has a valid hashtable.
 *         url is the url of the website
 *
 *   Post: Nothing is modified, the hashtable has been searched.
 *
 * Return: The website found, or NULL if one was not found.
 ******************************************************************************/
Website *hashSearch(ListHead *pList, const char *url);

/*******************************************************************************
 * Searches a hashtable for the specified url, and removes the found website
 * from the hashtable.
 *
 *    Pre: pList points to a list which is initialized and has a valid hashtable.
 *         url is the url of the website
 *
 *   Post: If the hashtable contained the url, it is removed from the hashtable.
 *
 * Return: The website removed, or NULL if one was not found.
 ******************************************************************************/
Website *hashRemove(ListHead *pList, const char *url);

/*******************************************************************************
 * Frees a hashtable from the specified ListHead
 *
 *    Pre: pList points to a list with a valid hashtable
 *
 *   Post: The hashtable is freed.
 *         pList->arySize is set to 0
 *         pList->pHash is set to NULL
 *
 * Return: --
 ******************************************************************************/
void hashFree(ListHead *pList);

/*******************************************************************************
 * Prints the efficiency of a hashtable.
 *
 *    Pre: pList points to a list with a valid hashtable
 *
 *   Post: The efficiency has been calculated and printed.
 *
 * Return: --
 ******************************************************************************/
void printEfficiency(ListHead *pList);

/*******************************************************************************
 * Lists the contents of a hashtable's buckets.
 *
 *    Pre: pList points to a list with a valid hashtable
 *
 *   Post: The data has been printed to stdout.
 *
 * Return: --
 ******************************************************************************/
void hashPrintList(ListHead *pList);


/*******************************************************************************
 * BstManager prototypes
 ******************************************************************************/

/*******************************************************************************
 * Creates a BSTfor the specified ListHead
 *
 *    Pre: pList points to a list with no BST.
 *
 *   Post: The BST has been created and is pointed to by pList->pTree.
 *
 * Return: --
 ******************************************************************************/
void bstCreate(ListHead *pList);

/*******************************************************************************
 * Attempts to insert Website into a BST.
 *
 *    Pre: pList points to a list which is initialized and has a valid BST.
 *         pWebsite points to a valid website.
 *
 *   Post: If the BST did not contain a website with the url, it is inserted.
 *         Otherwise, a warning is printed to the screen and the pointer is discarded.
 *
 * Return: true if the website was successfully inserted.
 *         false if the BST already contained an entry for the url.
 ******************************************************************************/
bool bstInsert(ListHead *pList, Website *pWebsite);

/*******************************************************************************
 * Searches a BST for the specified url.
 *
 *    Pre: pList points to a list which is initialized and has a valid hashtable.
 *         url is the url of the website
 *
 *   Post: Nothing is modified, the hashtable has been searched.
 *
 * Return: The website found, or NULL if one was not found.
 ******************************************************************************/
Website *bstSearch(ListHead *pList, const char *url);

/*******************************************************************************
 * Searches a BST for the specified url, and removes the found website
 * from the BST.
 *
 *    Pre: pList points to a list which is initialized and has a valid BST.
 *         url is the url of the website
 *
 *   Post: If the BST contained the url, it is removed from the BST.
 *
 * Return: The website removed, or NULL if one was not found.
 ******************************************************************************/
Website *bstRemove(ListHead *pList, const char *url);

/*******************************************************************************
 * Frees all of the elements and nodes from the BST from the specified ListHead.
 *
 *    Pre: pList points to a list with a valid BST
 *
 *   Post: Every Website in the BST is freed
 *         The BST is freed.
 *         pList->pTree is set to NULL
 *
 * Return: --
 ******************************************************************************/
void bstFreeAll(ListHead *pList);

/*******************************************************************************
 * Creates a QUEUE of the BST's elements in breadth first order.
 *
 *    Pre: pList points to a list with a valid BST
 *
 *   Post: The QUEUE is created and returned.
 *
 * Return: A QUEUE containing every element in breadth first order.
 ******************************************************************************/
QUEUE *bstTraverseBreadth(ListHead *pList);

/*******************************************************************************
 * Prints a BST formatted with indentation.
 *
 *    Pre: pList points to a list with a valid BST
 *
 *   Post: The BST has been printed to stdout.
 *
 * Return: --
 ******************************************************************************/
void bstPrintIndented(ListHead *pList);

/*******************************************************************************
 * Prints a BST inorder.
 *
 *    Pre: pList points to a list with a valid BST
 *
 *   Post: The BST has been printed to stdout.
 *
 * Return: --
 ******************************************************************************/
void bstPrintInorder(ListHead *pList);


/*******************************************************************************
 * WebsiteManager prototypes
 ******************************************************************************/

/*******************************************************************************
 * Allocates a new Website. Copies url and company into newly allocated strings.
 * All other fields are copied by value.
 *
 *    Pre: url and company are valid strings, the other parameters are correct.
 *
 *   Post: A new Website has been allocated,
 *         and initialized with the specified data.
 *
 * Return: A pointer to the new Website.
 ******************************************************************************/
Website *websiteCreate(const char *url,
                       const char *company,
                       int dailyPageViewThousands,
                       int rankTraffic,
                       int backLinkThousands,
                       int worthThousands);

/*******************************************************************************
 * Frees a Website, including its dynamically allocated url and company name.
 *
 *    Pre: pSite points to a valid Website.
 *
 *   Post: The Website, its url, and its company name are freed.
 *
 * Return: NULL
 ******************************************************************************/
Website *websiteFree(Website *pSite);

/*******************************************************************************
 * Prints a Website's url, followed by a newline.
 *
 *    Pre: pSite points to a valid Website.
 *
 *   Post: The Website is printed.
 *
 * Return: --
 ******************************************************************************/
void websitePrint(Website *pSite);

/*******************************************************************************
 * Prints a Website's url and info, on separate lines, ending with a newline
 *
 *    Pre: pSite points to a valid Website.
 *
 *   Post: The Website is printed.
 *
 * Return: --
 ******************************************************************************/
void websitePrintFull(Website *pSite);


/*******************************************************************************
 * MenuManager  prototypes
 ******************************************************************************/

typedef enum
{
    MENU_INSERT = 1,
    MENU_DELETE,
    MENU_SEARCH,
    MENU_PRINT_HASH,
    MENU_PRINT_INORDER,
    MENU_PRINT_INDENTED,
    MENU_PRINT_EFFICIENCY,
    MENU_SAVE,
    MENU_SAVE_AS,
    MENU_QUIT
} MENU_OPTION;



/*******************************************************************************
 * Prints the menu to the user, and loops until they enter a valid choice.
 *
 *    Pre: --
 *
 *   Post: The user has chosen a valid option
 *
 * Return: The user's selected option
 ******************************************************************************/
MENU_OPTION _promptMenu(void);


/*******************************************************************************
 * FileManager  prototypes
 ******************************************************************************/

/*******************************************************************************
 * Appends ".MOD" to a string.
 *
 *    Pre: fname is a null terminated c-string.
 *
 *   Post: A new c-string has been allocated and returned
 *
 * Return: The newly allocated string with fname + ".MOD"
 ******************************************************************************/
char *appendBackupExtension(const char *fname);

/*******************************************************************************
 * Counts the number of lines in a file
 *
 *    Pre: fname is the name of a file
 *
 *   Post: The file has been read and the lines counted.
 *
 * Return: The number of lines in the file, or -1 if the file could not be read.
 ******************************************************************************/
int countLines(const char *fname);


/*******************************************************************************
 * Reads a file and attempts to insert every valid Website into pHead.
 *
 *    Pre: fname is the name of a file
 *         pHead is a ListHead with a valid BST and Hash
 *
 *   Post: The file has been read and any valid Websites added
 *         An error is printed for every invalid website
 *
 * Return: true if the file was read, false if it could not be read
 ******************************************************************************/
bool readFile(const char *fname, ListHead *pHead);


/*******************************************************************************
 * Writes every Website in a QUEUE of Websites to a file
 *
 *    Pre: fname is the name of a file
 *         QUEUE is the queue of Websites
 *
 *   Post: The file has been written with every Website in the QUEUE's order.
 *         The QUEUE is destroyed.
 *
 * Return: true if the file was written, false if it could not be written
 ******************************************************************************/
bool writeFile(const char *fname, QUEUE *pQueue);


/*******************************************************************************
 * Copies the exact string to all lower cases.
 *
 *    Pre: dest is the destination string
 *         source is the source string
 *
 *   Post: Copies the exact string to all lower cases.
 *
 * Return: --
 ******************************************************************************/
void strcpyToLower(char *dest, const char *source);


/*******************************************************************************
 * Trims the new line character of a c-string by padding it with '\0'.
 *
 *    Pre: string is a valid c-string
 *
 *   Post: all non graphical characters at the end of the string are replaced
 *         with '\0'
 *
 * Return: --
 ******************************************************************************/
void trimNewLine(char *usInput);


/*******************************************************************************
 * Validates input (either file input or user input)
 *
 *    PR   type (input type)
 *         usInput (unsafe user-input to be validated
 *         && doesn't contain newline character)
 *
 *	 Post: validate user input with given input type
 *
 * Return: false (if user input is invalid)
 *         true (if user input is valid)
 ******************************************************************************/
bool validateInput(input_type type, char* usInput);


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
void MenuDriver(ListHead *head, char* sfName);


/*******************************************************************************
 * Initializes the program.
 *
 *    Pre: head is the header of the list
 *		   sfCur is the current safe file name
 *
 *   Post: Get input file name.
 *         Create data structures.
 *
 * Return: none
 ******************************************************************************/
void InitDriver(ListHead *head, char **sfCur);


/*******************************************************************************
 * Destroys hash and bst.
 *
 *    Pre: head is the header of the list
 *
 *   Post: Frees dynamically allocated memory of BST and HASH struct
 *
 * Return: none
 ******************************************************************************/
void DestroyDriver(ListHead *head);


/*******************************************************************************
 * Prompts user to enter input.
 *
 *    Pre: type is the input type
 *         msg is the message to be displayed for prompt
 *
 *   Post: Prompts user to enter the input.
 *         The input's new line character is trimmed.
 *         Validates the user input for its input type.
 *
 * Return: sInputBuffer is the validated input.
 ******************************************************************************/
char *promptInput(const input_type type, const char *msg);


/*******************************************************************************
 * Exits program with the given user request.
 *
 *    Pre: exitCode is the exit code returned with program exit
 *
 *   Post: exits program
 *
 * Return: --
 ******************************************************************************/
void exitOnUserRequest(int code);


/*******************************************************************************
 * Attempts to open backup file. If exists, prompt to discard backup file.
 *
 *    Pre: fBackup is the name of the backup file
 *         fSrc is the original file name entered by the user 
 *
 *   Post: Appends the backup file name to the original file name entered by user.
 *         Prompts to discard the backup file if exists
 *         Counts the number of lines in the backupfile.
 *
 * Return: -1 if backupfile was either discarded or not opened. Or,
 *         the number of lines read from the input file.
 ******************************************************************************/
int isBackupFileOpened(char** fBackup, char* fSrc);