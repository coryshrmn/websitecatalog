/* BstManager.c
 * Group 6
 * BST Manager
 *
 * Cory Sherman
 * Chris Huang
 * Gon Kim
 */

#include "WebsiteCatalog.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

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
void trimEnd(char *string)
{
    char *c;
    for(c = string + strlen(string); c != string; --c)
    {
        if(isgraph(*c))
            return;
        else
            *c = '\0';
    }
}

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
void trimNewLine(char *usInput) {
	size_t len = 0;

	len = strlen(usInput);
	if (usInput[len - 1] == '\n') {
		usInput[len - 1] = '\0';
	}
}

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
void *validate(void *pointer)
{
    if(!pointer)
    {
        printf("Fatal error! Quitting...");
        exit(EXIT_FAILURE);
    }
    return pointer;
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



