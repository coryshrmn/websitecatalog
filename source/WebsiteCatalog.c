/* WebsiteCatalog.c
 * Website Catalog Main
 *
 * Cory Sherman
 * Gon Kim
 */

#include "WebsiteCatalog.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    ListHead head; // head of the list
    char buff[1024];
    char *fname;

    int numLines;

    MENU_OPTION menuChoice;

    //prompt input file name
    do
    {
        printf("Input file name:\n>");
        fflush(stdout);
        validate(fgets(buff, 1024, stdin));
        trimEnd(buff);
        numLines = countLines(buff);
        if(numLines == 1)
            printf("File not found \"%s\"!\n", buff);
    } while(numLines == -1);

    fname = malloc(strlen(buff) + 1);
    strcpy(fname, buff);

    //TODO optional: prompt user to discard or load modified file


    //create data structures
    hashCreate(&head, numLines);
    bstCreate(&head);

    readFile(fname, &head);
    
    //loop menu
    do
    {
        switch(menuChoice = promptMenu())
        {
        case MENU_INSERT:
        {
            Website tempWebsite;
            Website *pCreate;

            printf("Enter URL to add:\n>");
            fflush(stdout);
            validate(fgets(buff, 1024, stdin));
            trimEnd(buff);
            strcpyToLower(buff, buff);

            tempWebsite.url = buff;

            if(!hashInsert(&head, &tempWebsite))
            {
                break;
            }
            hashRemove(&head, buff);

            pCreate = malloc(sizeof(Website));
            pCreate->url = malloc(strlen(buff) + 1);
            strcpy(pCreate->url, buff);

            printf("Enter company name:\n>");
            fflush(stdout);
            validate(fgets(buff, 1024, stdin));
            trimEnd(buff);
            pCreate->company = malloc(strlen(buff) + 1);
            strcpy(pCreate->company, buff);

            printf("Enter daily page view thousands:\n>");
            fflush(stdout);
            validate(fgets(buff, 1024, stdin));
            pCreate->dailyPageViewThousands = atoi(buff);

            printf("Enter traffic rank:\n>");
            fflush(stdout);
            validate(fgets(buff, 1024, stdin));
            pCreate->rankTraffic = atoi(buff);

            printf("Enter back link thousands:\n>");
            fflush(stdout);
            validate(fgets(buff, 1024, stdin));
            pCreate->backLinkThousands = atoi(buff);

            printf("Enter website worth thousands:\n>");
            fflush(stdout);
            validate(fgets(buff, 1024, stdin));
            pCreate->websiteWorthThousands = atoi(buff);

            listInsert(&head, pCreate);
        }

            break;
        case MENU_DELETE:
            printf("Enter URL to delete:\n>");
            fflush(stdout);
            validate(fgets(buff, 1024, stdin));
            trimEnd(buff);
            strcpyToLower(buff, buff);
            printf(listRemove(&head, buff) ? "Removed.\n" : "Not found!\n");
            break;
        case MENU_SEARCH:
        {
            Website *pFound;
            printf("Enter URL to search for:\n>");
            fflush(stdout);
            validate(fgets(buff, 1024, stdin));
            trimEnd(buff);
            strcpyToLower(buff, buff);
            pFound = hashSearch(&head, buff);
            if(pFound)
                websitePrintFull(pFound);
            else
                printf("Not found!\n");
        } break;
        case MENU_PRINT_HASH:
            hashPrintList(&head);
            break;
        case MENU_PRINT_INORDER:
            bstPrintInorder(&head);
            break;
        case MENU_PRINT_INDENTED:
            bstPrintIndented(&head);
            break;
        case MENU_PRINT_EFFICIENCY:
            printEfficiency(&head);
            break;
        case MENU_SAVE_AS:
            printf("Enter file name to save:\n>");
            fflush(stdout);
            validate(fgets(buff, 1024, stdin));
            trimEnd(buff);
            printf(writeFile(buff, bstTraverseBreadth(&head)) ?
                             "File written\n" :
                             "File could not be written!\n");
            break;
        case MENU_QUIT:
        {
            char *modName = appendBackupExtension(fname);
            if(!writeFile(modName, bstTraverseBreadth(&head)))
                printf("Autosave file could not be written!\n");
            else
                printf("Autosaved to: %s\n", modName);
            free(modName);
        }
            break;
        }
    } while(menuChoice != MENU_QUIT);

    hashFree(&head);
    bstFreeAll(&head);


    free(fname);
    
    return EXIT_SUCCESS;
}
