/* 
 *  Drivers.c
 *  calls functions to initialize functions
 *      Developer:      Gon Kim (imgonkim@gmail.com)
 *      Initial Commit:  03182013_174020
 *      Last Updated:    03182013_174020
 */
#include "../header/WebsiteCatalog.h"

void InitDriver (ListHead *pHead, FILE** fPtr, char **fname) {
    int nLines = 0;

    *fPtr = initFileStream(fname, &nLines);
    if (*fPtr) {
        hashCreate(pHead, nLines);
        bstCreate(pHead);
    }
}

void BuildDriver (ListHead *pHead, FILE* fPtr, const char *fname) {
    Website *curWebsite = NULL;
    bool success = false;
    
    do {
        curWebsite = getSingleWebsite(fPtr);
        success = listInsert(pHead, curWebsite);
    } while (!success);
}

void PrintDriver (ListHead *pHead) {
    printf("hashPrintList(&head)\n");
    hashPrintList(pHead);

    printf("\n\nbstPrintIndented(&head)\n");
    bstPrintIndented(pHead);

    printf("\n\nbstPrintInorder(&head)\n");
    bstPrintInorder(pHead);
}

void MenuDriver (ListHead *pHead, FILE** fPtr, char **fname) {
    bool isDataModified = false;
    
    MenuManager(pHead, *fPtr, *fname, &isDataModified);
}


void DestroyDriver (ListHead *pHead) {
    hashFree(pHead);
    bstFreeAll(pHead);
}


