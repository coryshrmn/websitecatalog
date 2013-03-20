/*
 * FileManager.c
 * contains necesary information with
 * current and last session management
 *
 * Gon Kim
 * Cory Sherman
 */

#include "WebsiteCatalog.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BACKUP_FILENAME_EXTENSION ".BAK"


#define MSG_PROMPT_DISCARD_LAST_SESSION         "Discard last session (Y/N)? "
#define VERB_FILEOPEN(name, mode)               ">VERBOSE:  File \"%s\" is opened for %s mode.\n", name, mode
#define VERB_FILE_REOPEN(name, mode)            ">VERBOSE:  File \"%s\" is re-opening for mode \"%s\"", name, mode
#define VERB_LAST_SESSION_FOUND                 ">VERBOSE:  Last session was not saved.\n"
#define VERB_LAST_SESSION_DISCARDED             ">VERBOSE:  Last session was discarded.\n"
/*******************************************************************************
 * FileManager private prototypes
 *
 * static Website *_readWebsite(char *line);
******************************************************************************/
static char* _addFileExtension(const char *fSource, const char *fExt);
static bool _discardLastSessionOrNot();

/*******************************************************************************
 * Reads a single Website from a line of text
 *
 *    Pre: line is a c-string
 *
 *   Post: line is modified.
 *         A Website is created and returned,
 *         Or NULL is returned if the line was invalid.
 *
 * Return: The new Website, or NULL
 ******************************************************************************/
static Website *_readWebsite(char *line);


/*******************************************************************************
 * FileManager function definitions
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
char *appendBackupExtension(const char *fname)
{
    char *output;
    int len;
    len = strlen(fname);
    output = malloc(len + 5);
    strncpy(output, fname, len);
    strcpy(output + len, ".BAK");
    return output;
}

/*******************************************************************************
 * Counts the number of lines in a file
 *
 *    Pre: fname is the name of a file
 *
 *   Post: The file has been read and the lines counted.
 *
 * Return: The number of lines in the file, or -1 if the file could not be read.
 ******************************************************************************/
int countLines(const char *fname)
{
    FILE *fin;
    int totalLines;
    char buff[1024];
    fin = fopen(fname, "r");
    if(!fin)
        return -1;

    for(totalLines = 0; fgets(buff, 1024, fin); ++totalLines);

    fclose(fin);

    return totalLines;
}


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
bool readFile(const char *fname, ListHead *pHead)
{
    FILE *fin;
    char buff[1024];
    fin = fopen(fname, "r");
    if(!fin)
        return false;
    while(fgets(buff, 1024, fin))
    {
        Website *pWebsite = _readWebsite(buff);
        if(pWebsite)
            listInsert(pHead, pWebsite);
        else
            printf("Invalid line: %s", buff);
    }
    fclose(fin);
    return true;
}


/*******************************************************************************
 * Reads a single Website from a line of text
 *
 *    Pre: line is a c-string
 *
 *   Post: line is modified.
 *         A Website is created and returned,
 *         Or NULL is returned if the line was invalid.
 *
 * Return: The new Website, or NULL
 ******************************************************************************/
static Website *_readWebsite(char *line)
{
    char *fields[6];

    char *nextSemi;
    int i;
    nextSemi = line - 1;
    for(i = 0; i != 6; ++i)
    {
        fields[i] = nextSemi + 1;
        nextSemi = strchr(nextSemi + 1, ';');
        if(!nextSemi)
            return NULL;
        *nextSemi = '\0';
    }

    return websiteCreate(fields[0],         //url
                         fields[1],         //company name
                         atoi(fields[2]),   //daily page views 
                         atoi(fields[3]),   //traffic rank
                         atoi(fields[4]),   //back links
                         atoi(fields[5]));  //worth
}


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
bool writeFile(const char *fname, QUEUE *pQueue)
{
    Website *pWebsite;
    FILE *fout = fopen(fname, "w");
    if(!fout)
    {
        destroyQueue(pQueue);
        return false;
    }

    while(dequeue(pQueue, (void**)&pWebsite))
    {
       fprintf(fout, "%s;%s;%d;%d;%d;%d;\n", pWebsite->url,
                                       pWebsite->company,
                                       pWebsite->dailyPageViewThousands,
                                       pWebsite->rankTraffic,
                                       pWebsite->backLinkThousands,
                                       pWebsite->websiteWorthThousands);
    }
    fclose(fout);
    destroyQueue(pQueue);
    return true;
}

/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
bool doesLastSessionExist(char** fDest, char* fSrc) {
	FILE* fPtr;             // file pointer for input stream
    bool session = false;
    
	*fDest = _addFileExtension(fSrc, BACKUP_FILENAME_EXTENSION);
	fPtr = fopen(*fDest, FILEMODE_READONLY);
    if(fPtr) {
    	printf(VERB_LAST_SESSION_FOUND);
        if (!_discardLastSessionOrNot()) {
            session = true;
        }
        fclose(fPtr);
    }
   
    return session;
}

/*
 * Appends file extension.
 * malloc 
 */
static char* _addFileExtension(const char *fSrc, const char *fExt) {
	char *fDest;        // safe name
    
    fDest = malloc(strlen(fSrc) + strlen(fExt) + 1);
	// get: backup filename
	strcpy(fDest, fSrc);
	strcat(fDest, BACKUP_FILENAME_EXTENSION);
    
	return fDest;
}



static bool _discardLastSessionOrNot() {
    bool isValid = false;
    bool isDiscarded = false;
    char buff[1024];
    
	// prompt: do you wish to discard?
    do {
		printf(MSG_PROMPT_DISCARD_LAST_SESSION);
		fflush(stdout);
		validate(fgets(buff, 1024, stdin));
        //        trimEnd(buff);
		trimNewLine(buff);
		if (!validateInput(INPUT_TYPE_DISCARD, buff)) {
            printf(ERR_INVALID_INPUT);
		} else {
            isValid = true;
		}
        
	} while (!isValid);
    
	switch (buff[0]) {
        case 'Q':
        case 'q':
            exitOnUserRequest(EXIT_ON_USER_REQUEST);
            break;
        case 'Y':
        case 'y':
            isDiscarded = true;
            break;
        case 'N':
        case 'n':
            isDiscarded = false;
            break;
	}
    
    return isDiscarded;
    
}
