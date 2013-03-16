/* BstManager.c
 * Group 6
 * WebsiteCatalog main
 *
 * Cory Sherman
 */

#include "WebsiteCatalog.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * WebsiteCatalog Private Prototypes
 ******************************************************************************/



/*******************************************************************************
 * Main entry point for the program
 ******************************************************************************/
int main(void)
{
    ListHead head;

    //TODO input

    hashCreate(&head, 25);
    bstCreate(&head);

    listInsert(&head, websiteCreate("google.com", "Google", 1000, 1, 2000, 3000));
    listInsert(&head, websiteCreate("yahoo.com", "Yahoo", 4000, 2, 5000, 6000));

    hashPrintList(&head);

    bstPrintIndented(&head);
    bstPrintInorder(&head);


    //TODO menu

    //TODO quit

    hashFree(&head);
    bstFreeAll(&head);
    return EXIT_SUCCESS;
}

