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
	bool isDataModified = false;
	int numLines;
	FILE *fPtr;
	MENU_OPTION menuChoice;
  Website tempWebsite;
    
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
	if (checkLastSession(&fBacName, fname)) {
		if (!strcmp(fBacName, fname)) {
			isDataModified = true;
		}
		tmp = fname;
		fname = fBacName;
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
                    strcpyToLower(buff, buff);
                    if (validateInput(INPUT_TYPE_URL, buff)) {
                        valid = true;
                    }
                } while (!valid);
                // added

                tempWebsite.url = buff;
                if (!hashInsert(&head, &tempWebsite)) {
                    break;
                }
                hashRemove(&head, buff);
                
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
                
                if (listInsert(&head, pCreate)) {
                    isDataModified = true;
                }
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
                    strcpyToLower(buff, buff);
                    if (validateInput(INPUT_TYPE_URL, buff)) {
                        valid = true;
                    }
                } while (!valid);
                if (listRemove(&head, buff)) {
                    printf("Removed.\n");
                    isDataModified = true;
                } else {
                    printf("Not found!\n");
                }
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
                    strcpyToLower(buff, buff);
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
                if (writeFile(fname, bstTraverseBreadth(&head))) {
                    isDataModified = false;
                    printf("File written\n");
                } else {
                    printf("File could not be written!\n");
                }
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
                if (writeFile(buff, bstTraverseBreadth(&head))) {
                    printf("File written\n");
                    fname = buff;
                    isDataModified = false;
                } else {
                    printf("File could not be written!\n");
                }
                
                break;
            case MENU_QUIT: {
                //                char *modName = appendBackupExtension(fname);
                //                if (!writeFile(modName, bstTraverseBreadth(&head)))
                //                    printf("Autosave file could not be written!\n");
                if (isDataModified) {
                    if (!writeFile(fname, bstTraverseBreadth(&head))) {
                        printf("Autosave file could not be written!\n");
                    }
                    
                    printf("Autosaved to: %s\n", fname);
                }
                free(fBacName);
            }
                break;
		}
	} while (menuChoice != MENU_QUIT);
    
	hashFree(&head);
	bstFreeAll(&head);
    
    if (fname) 
	free(fname);
    
	return EXIT_SUCCESS;
}
