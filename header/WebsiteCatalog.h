 /* WebsiteCatalog.h
  * Group 6
  * Header File
  *
  * Cory Sherman
  * Gon Kim
  * Chris Huang
  */
#include <stdio.h>
#include <limits.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>
#include "constants.h"
#include "queueADT.h"

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
 * Validates the system is not out of memory.
 * If alloc is NULL, exit(102) is called.
 *
 *    Pre: alloc is the memory for which allocation was attempted.
 *
 *   Post: alloc is not NULL, or exit(102) is called.
 *
 * Return: alloc
 ******************************************************************************/
void *validate(void *alloc);

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
Website *websiteCreate(const char *url, const char *company, int dailyPageViewThousands, int rankTraffic, int backLinkThousands, int worthThousands);

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

void strcpyToLower(char *dest, const char *source);



/*
 *  initFileStream
 *  intializes file stream to get ready for the program.
 *
 *  PRE:        none
 *
 *  POST:       none
 *              sFileName (safe file name)
 *              nLines (number of lines from input file)
 *
 *  RETURN:     fPtr (updated file pointer)
 *
 */
FILE* initFileStream(char **sFileName, int *nLines);
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
menu_type getMenuSelection(void);
/*
 * validateInput
 * validates input (either file input or user input)
 *
 *  PRE:    type (input type)
 *          usInput (unsafe user-input to be validated
 *                   && doesn't contain newline character)
 *
 *  POST:   validate user input with given input type
 *
 *  RETURN:  INPUT_VALUE_INVALID (if user input is invalid)
 *          INPUT_VALUE_VALID (if user input is valid)
 *
 */

input_value validateInput(input_type type, char* usInput);
/*
 * getSingleWebsite
 * parses information from the file pointer:
 *
 *  PRE:    fPtr (file pointer; readonly; from input file stream)
 *
 *  POST:   All fields are completedly parsed from the input file stream
 *
 *  RETURN:  Website (fields are completedly parsed)
 *
 */
Website* getSingleWebsite(FILE* fPtr);
/*******************************************************************************
 * Copies a string as lower case.
 *
 *    Pre: source is the original string
 *         dest is long enough to hold the original string
 *
 *   Post: dest is the lowercase version of source, with '\0' terminator.
 *
 * Return: --
 ******************************************************************************/
input_value getUserSelection(input_type type, const char *msg);

/*******************************************************************************
 * Exits program with the given user request.
 *
 *    Pre: exitCode is the exit code returned with program exit
 *
 *   Post: exits program
 *
 * Return: --
 ******************************************************************************/
void exitOnUserRequest (const int exitCode);
