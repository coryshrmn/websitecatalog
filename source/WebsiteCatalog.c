/*******************************************************************************
 * WebsiteCatalog.c
 *
 * Developer(s):
 * 		Cory Sherman	(coryshrmn@gmail.com)
 * 		Gon Kim			(imgonkim@gmail.com)
 *		Chris Huang		(christopher.e.huang@gmail.com)
 *
 * Contains the main entry point and drivers of the program.
 *
 ******************************************************************************/

#include "WebsiteCatalog.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#include <crtdbg.h>
#endif

int main(void) {
	ListHead head; // head of the list
	char *sfName = NULL; // safe filename

	InitDriver(&head, &sfName);
	readFile(sfName, &head);
	MenuDriver(&head, sfName);
    free(sfName);
	DestroyDriver(&head);

	return EXIT_SUCCESS;
}

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
void InitDriver(ListHead *head, char **sfCur) {
	bool isValid = false;
	int numLines;
	char *sfBackup;
	char *sfOrig; // current file name

	// get file name to open
	do {
		sfOrig = promptInput(INPUT_TYPE_FILENAME, MSG_PROMPT_FILENAME);

		// backup file or original file?)
		numLines = isBackupFileOpened(&sfBackup, sfOrig);
        
		if (numLines == -1) { // backup file not opened
			*sfCur = sfOrig;
			// count number of lines of the input file
			numLines = countLines(*sfCur);
			if (-1 == numLines) { // couldn't open backup file
				printf(ERR_COULD_NOT_OPEN_FILE(*sfCur));
				free(*sfCur);
			} else {
				isValid = true;
			}
        
		} else { // backup file opened
			*sfCur = sfBackup;
			free(sfOrig);
			isValid = true;
		}
	} while (!isValid);

	//create data structures
	hashCreate(head, numLines);
	bstCreate(head);

}
/*******************************************************************************
 * Destroys hash and bst.
 *
 *    Pre: head is the header of the list
 *
 *   Post: Frees dynamically allocated memory of BST and HASH struct
 *
 * Return: none
 ******************************************************************************/
void DestroyDriver(ListHead *head)
{
	hashFree(head);
	bstFreeAll(head);
    #ifdef _MSC_VER
    printf(_CrtDumpMemoryLeaks() ? "Memory leaks!\n" : "No memory leaks.\n");
    #endif
}

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
char *promptInput(const input_type type, const char *msg) {
	char buff[MAX_LENGTH_INPUT];    // buffer input
	char *sInputBuffer;             // safe filename
	bool isValid = false;           // is user input valid?

	do {
		printf("%s", msg);
		fflush(stdout);
		validate(fgets(buff, MAX_LENGTH_FILENAME, stdin));
		trimNewLine(buff);

		// check: if user wishes to exit the program
		if (!strcmp(buff, USERINPUT_QUIT)) {
			exitOnUserRequest(EXIT_ON_USER_REQUEST);
		}

		// validate: user input
		if (validateInput(type, buff)) {
			sInputBuffer = malloc((strlen(buff) + 1));
			strcpy(sInputBuffer, buff);
			isValid = true;
		}

	} while (!isValid);

	return sInputBuffer;
}
