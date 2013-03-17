/* BstManager.c
 * Group 6
 * BST Manager
 *
 * Cory Sherman
 * Chris Huang
 */

#include "../header/WebsiteCatalog.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

/*******************************************************************************
 * Validates the system is not out of memory.
 * If alloc is NULL, exit(102) is called.
 *
 *    Pre: alloc is the memory for which allocation was attempted.
 *
 *   Post: alloc is not NULL, or exit(102) is called.
 *
 * Return: --
 ******************************************************************************/
void *validate(void *alloc)
{
    if(!alloc)
    {
        printf("Out of memory! Quitting...");
        exit(EXIT_FAILURE);
    }
    return alloc;
}

/*******************************************************************************
 * Prints an integer with commas every 3 digits. Not padded.
 *
 *    Pre: val is the value to print
 *
 *   Post: val is printed to the screen, with commas every 3 digits.
 *
 * Return: --
 ******************************************************************************/
void printIntCommas(int val)
{
    int t;
    if(val < 0)
    {
        printf("-");
        val = -val;
    }
    for(t = 1000; t <= val; t *= 1000);
    t /= 1000;
    printf("%d", val / t);
    while((t /= 1000) != 0)
    {
        val %= 1000;
        printf(",%03d", val / t);
    }
}

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
void strcpyToLower(char *dest, const char *source)
{
    const char *sourceWalk;
    char *destWalk;
    for(sourceWalk = source, destWalk = dest; *sourceWalk != '\0'; ++sourceWalk, ++destWalk)
    {
        *destWalk = tolower(*sourceWalk);
    }
    *destWalk = '\0';
}

/*******************************************************************************
 * Exits program with the given user request.
 *
 *    Pre: exitCode is the exit code returned with program exit
 *
 *   Post: exits program
 *
 * Return: --
 ******************************************************************************/
void exitOnUserRequest (const int exitCode) {
    exit(exitCode);
}

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
input_value getUserSelection(input_type type, const char *msg) {
	char usInput[MAX_LENGTH_INPUT];
	input_value value = INPUT_VALUE_INVALID;
    
	do {
		printf("%s", msg);
		fgets(usInput, MAX_LENGTH_INPUT, stdin);
        
		// trim: '\n'
		usInput[strlen(usInput) - 1] = '\0';
        
		// validate: user input
		value = validateInput(type, usInput);
		if (INPUT_VALUE_QUIT == value) {
			exit(EXIT_ON_USER_REQUEST);
		}
	} while (INPUT_VALUE_INVALID == value);
	return value;
}
