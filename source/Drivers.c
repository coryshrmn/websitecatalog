/* 
 *  Drivers.c
 *  calls functions to initialize functions
 *      Developer:      Gon Kim (imgonkim@gmail.com)
 *      Initial Commit:  03182013_174020
 *      Last Updated:    03182013_174020
 */
#include "../header/WebsiteCatalog.h"

<<<<<<< HEAD
void InitDriver (ListHead *head, FILE** fPtr, char **fname) {
=======
void InitDriver (ListHead *pHead, FILE** fPtr, char **fname) {
>>>>>>> bec9cffd7bdd2d9480d36ef2def067325a7dc40c
    int nLines = 0;

    *fPtr = initFileStream(fname, &nLines);
    if (*fPtr) {
<<<<<<< HEAD
        hashCreate(head, nLines);
        bstCreate(head);
    }
}

void BuildDriver (ListHead *head, FILE* fPtr, const char *fname) {
=======
        hashCreate(pHead, nLines);
        bstCreate(pHead);
    }
}

void BuildDriver (ListHead *pHead, FILE* fPtr, const char *fname) {
>>>>>>> bec9cffd7bdd2d9480d36ef2def067325a7dc40c
    Website *curWebsite = NULL;
    bool success = false;
    
    do {
        curWebsite = getSingleWebsite(fPtr);
<<<<<<< HEAD
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
=======
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
>>>>>>> bec9cffd7bdd2d9480d36ef2def067325a7dc40c
}


