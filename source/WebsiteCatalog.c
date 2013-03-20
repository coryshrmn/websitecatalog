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

int main(void) {
	ListHead head; // head of the list
	char buff[1024];
	char *fBacName;
    char *fname;
    char *tmp;
	bool valid;
	int numLines;
    FILE *fPtr;
	MENU_OPTION menuChoice;
    
    
    
	//prompt input file name
	valid = false;
	do {
		printf("Input file name:\n>");
		fflush(stdout);
		validate(fgets(buff, 1024, stdin));
        //        trimEnd(buff);
		trimNewLine(buff);
		if (!validateInput(INPUT_TYPE_FILENAME, buff)) {
			numLines = -1;
		} else {
			numLines = countLines(buff);
			if (numLines == 1)
				printf("File not found \"%s\"!\n", buff);
		}
        
	} while (numLines == -1);

	fname = malloc(strlen(buff) + 1);
	strcpy(fname, buff);
       
    //TODO optional: prompt user to discard or load modified file
    if(doesLastSessionExist(&fBacName, fname)) {
        tmp = fname;
        fname = fBacName;
        free(fBacName);
        tmp = NULL;
    }    
    
    //create data structures
	hashCreate(&head, numLines);
	bstCreate(&head);
    

    readFile(fname, &head);
    
	//loop menu
	valid = false;
	do {
		switch (menuChoice = promptMenu()) {
            case MENU_INSERT: {
                Website *pCreate;
                do {
                    printf("Enter URL to add:\n>");
                    fflush(stdout);
                    validate(fgets(buff, 1024, stdin));
                    //          trimEnd(buff);
                    trimNewLine(buff);
                    if (validateInput(INPUT_TYPE_URL, buff)) {
                        valid = true;
                    }
                } while (!valid);
                
                strcpyToLower(buff, buff);
                if (hashSearch(&head, buff)) {
                    printf("Already in catalog!\n");
                    break;
                }
                
                pCreate = malloc(sizeof(Website));
                pCreate->url = malloc(strlen(buff) + 1);
                strcpy(pCreate->url, buff);
                
                valid = false;
                do {
                    printf("Enter company name:\n>");
                    fflush(stdout);
                    validate(fgets(buff, 1024, stdin));
                    //          trimEnd(buff);
                    trimNewLine(buff);
                    if (validateInput(INPUT_TYPE_COMPANY, buff)) {
                        valid = true;
                    }
                } while (!valid);
                pCreate->company = malloc(strlen(buff) + 1);
                strcpy(pCreate->company, buff);
                
                valid = false;
                do {
                    printf("Enter daily page view thousands:\n>");
                    fflush(stdout);
                    validate(fgets(buff, 1024, stdin));
                    //          trimEnd(buff);
                    trimNewLine(buff);
                    if (validateInput(INPUT_TYPE_DAILY_PAGE_VIEW, buff)) {
                        valid = true;
                    }
                } while (!valid);
                pCreate->dailyPageViewThousands = atoi(buff);
                
                valid = false;
                do {
                    printf("Enter traffic rank:\n>");
                    fflush(stdout);
                    validate(fgets(buff, 1024, stdin));
                    //          trimEnd(buff);
                    trimNewLine(buff);
                    if (validateInput(INPUT_TYPE_RANK_TRAFFIC, buff)) {
                        valid = true;
                    }
                } while (!valid);
                pCreate->rankTraffic = atoi(buff);
                
                valid = false;
                do {
                    printf("Enter back link thousands:\n>");
                    fflush(stdout);
                    validate(fgets(buff, 1024, stdin));
                    //          trimEnd(buff);
                    trimNewLine(buff);
                    if (validateInput(INPUT_TYPE_BACK_LINK, buff)) {
                        valid = true;
                    }
                } while (!valid);
                pCreate->backLinkThousands = atoi(buff);
                
                valid = false;
                do {
                    printf("Enter website worth thousands:\n>");
                    fflush(stdout);
                    validate(fgets(buff, 1024, stdin));
                    //          trimEnd(buff);
                    trimNewLine(buff);
                    if (validateInput(INPUT_TYPE_WEBSITE_WORTH, buff)) {
                        valid = true;
                    }
                } while (!valid);
                pCreate->websiteWorthThousands = atoi(buff);
                
                listInsert(&head, pCreate);
            }
                
                break;
            case MENU_DELETE:
                valid = false;
                do {
                    printf("Enter URL to delete:\n>");
                    fflush(stdout);
                    validate(fgets(buff, 1024, stdin));
                    //          trimEnd(buff);
                    trimNewLine(buff);
                    if (validateInput(INPUT_TYPE_URL, buff)) {
                        valid = true;
                    }
                } while (!valid);
                printf(listRemove(&head, buff) ? "Removed.\n" : "Not found!\n");
                break;
            case MENU_SEARCH: {
                Website *pFound;
                valid = false;
                do {
                    printf("Enter URL to search for:\n>");
                    fflush(stdout);
                    validate(fgets(buff, 1024, stdin));
                    //          trimEnd(buff);
                    trimNewLine(buff);
                    if (validateInput(INPUT_TYPE_URL, buff)) {
                        valid = true;
                    }
                } while (!valid);
                pFound = hashSearch(&head, buff);
                if (pFound)
                    websitePrintFull(pFound);
                else
                    printf("Not found!\n");
            }
                break;
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
            case MENU_SAVE:
                printf(
                       writeFile(fname, bstTraverseBreadth(&head)) ?
                       "File written\n" : "File could not be written!\n");
                break;
            case MENU_SAVE_AS:
                valid = false;
                do {
                    printf("Enter file name to save:\n>");
                    fflush(stdout);
                    validate(fgets(buff, 1024, stdin));
                    //          trimEnd(buff);
                    trimNewLine(buff);
                    if (validateInput(INPUT_TYPE_FILENAME, buff)) {
                        valid = true;
                    }
                } while (!valid);
                printf(
                       writeFile(buff, bstTraverseBreadth(&head)) ?
                       "File written\n" : "File could not be written!\n");
                break;
            case MENU_QUIT: {
                char *modName = appendBackupExtension(fname);
                if (!writeFile(modName, bstTraverseBreadth(&head)))
                    printf("Autosave file could not be written!\n");
                else
                    printf("Autosaved to: %s\n", modName);
                free(modName);
            }
                break;
		}
	} while (menuChoice != MENU_QUIT);
    
	hashFree(&head);
	bstFreeAll(&head);
    
	free(fname);
    
	return EXIT_SUCCESS;
}