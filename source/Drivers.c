/* 
 *  Drivers.c
 *  calls functions to initialize functions
 *      Developer:      Gon Kim (imgonkim@gmail.com)
 *      Initial Commit:  03182013_174020
 *      Last Updated:    03182013_174020
 */
#include "../header/WebsiteCatalog.h"

void InitDriver (ListHead *head, FILE** fPtr, char **fname) {
    int nLines = 0;

    *fPtr = initFileStream(fname, &nLines);
    if (*fPtr) {
        hashCreate(head, nLines);
        bstCreate(head);
    }
}

void BuildDriver (ListHead *head, FILE* fPtr, const char *fname) {
    Website *curWebsite = NULL;
    bool success = false;
    
    do {
        curWebsite = getSingleWebsite(fPtr);
        success = listInsert(head, curWebsite);
    } while (success);
}

void PrintDriver (ListHead head) {
    printf("hashPrintList(&head)\n");
    hashPrintList(&head);

    printf("\n\nbstPrintIndented(&head)\n");
    bstPrintIndented(&head);

    printf("\n\nbstPrintInorder(&head)\n");
    bstPrintInorder(&head);
}

void MenuDriver (ListHead *head, FILE** fPtr, char **fname) {
    bool isDataModified = false;
    
    MenuManager(head, *fPtr, *fname, &isDataModified);
}


void DestroyDriver (ListHead *head) {
    hashFree(head);
    bstFreeAll(head);
}


