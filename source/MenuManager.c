/* MenuManager.c
 * Menu Manager
 * contains functions for handling menus
 *
 * Gon Kim
 * Cory Sherman
 */

#include "WebsiteCatalog.h"
#include <stdio.h>


const char *MENU_MESSAGE = "\n"
                           "1 - Insert a Website\n"
                           "2 - Delete a Website by URL\n"
                           "3 - Search for a Website by URL\n"
                           "4 - Print hash buckets\n"
                           "5 - Print BST in order\n"
                           "6 - Print BST indented\n"
                           "7 - Print hash efficiency\n"
                           "8 - Save\n"
                           "9 - Save as...\n"
                           "10 - Quit\n"
                           ">";


/*******************************************************************************
 * Prints the menu to the user, and loops until they enter a valid choice.
 *
 *    Pre: --
 *
 *   Post: The user has chosen a valid option
 *
 * Return: The user's selected option
 ******************************************************************************/
MENU_OPTION promptMenu(void)
{
    bool valid = false;
    int choice;
    
    do
    {
        char line[256];
        printf("%s", MENU_MESSAGE);
        fflush(stdout);
        validate(fgets(line, 256, stdin));
        trimNewLine(line);
        if (validateInput(INPUT_TYPE_MENU, line)) {
            choice = atoi(line);
            valid = true;
        }
//        if(!(valid = choice >= 1 && choice <= 9))
//        {
//            printf("Invalid option.\n");
//        }
    } while(!valid);

    return choice;
}

