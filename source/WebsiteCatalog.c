#include "WebsiteCatalog.h"

int main (void) {
    ListHead head; // head of the list
    Website *curWebsite; // website struct
    menu_type menu; // menu type
    FILE *fPtr = NULL; // file pointer
    char *fname = NULL; // file name
    int nLines = 0; // number of input line
    bool isDataModified = false;        // is data modified?
    
    
    InitDriver(&head, &fPtr, &fname);
    BuildDriver(&head, fPtr, fname);
    PrintDriver (&head);
    MenuDriver (&head, &fPtr, &fname);
    DestroyDriver (&head);
    
    
    return 0;
}
