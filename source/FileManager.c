/*
 * FileManager.c
 * contains necesary information with
 * current and last session management
 *
 * Developer:           Gon Kim (imgonkim@gmail.com)
 * Initial Commit:      03162013_221816
 * Last Major Update:   03172013_071800
 *
 */
#include "../header/WebsiteCatalog.h"
#include "../header/FileManager.h"
/*
 *  initFileStream
 *  intializes file stream to get ready for the program.
 *
 *  PRE:        none
 *
 *  POST:       sFileName (safe file name)
 *              nLines (number of lines from input file)
 *
 *  RETURN:     fPtr (updated file pointer)
 *
 */
FILE* initFileStream(char **sFileName, int *nLines) {
	FILE *fPtr = NULL; // file pointer
	char *usFileName = NULL;    // unsafe file name
    
	*sFileName = NULL;
    //if you do this, you can no longer dereference sFileName
	//sFileName = NULL;
    
	// open filestream either from backup file or original
	do {
		// open: last session
		usFileName = promptFileName(MSG_PROMPT_FILENAME);
		fPtr = _openLastSessionFileStream(usFileName);
        
		if (!fPtr) { /* error in opening backup file */
			fPtr = fopen(usFileName, FILEMODE_READONLY);
			if (!fPtr) { /* error in opening file */
				printf(ERR_COULD_NOT_OPEN_FILE(usFileName));
			} else { /* current session successfully opened */
				printf(VERB_FILEOPEN(usFileName, FILEMODE_READONLY));
			}
		} else { /* backup file exists */
			fPtr = _promptDiscardLastSession(fPtr);
			if (!fPtr) { // backup file discarded
				printf(VERB_LAST_SESSION_DISCARDED);
			}
		}
	} while (!fPtr);
    
	*sFileName = usFileName; /* file name is now safe */
    
	*nLines = _getNumberOfLines(fPtr);
    rewind(fPtr);
	return fPtr;
}

// TODO:
void writeToFile(ListHead *head, FILE* fPtr) {
    
}

bool closeFile(FILE* fPtr, char *name) {
    if ((fclose(fPtr))) { // close failed
        return false;
    };
    if (name) {
        free(name);
    }

    return true;
}
/*
 *  reopenCurrentFileStream
 *  handles file I/O for current session.
 *
 *  PRE:        sFileName (file name)
 *              mode (file mode)
 *
 *  POST:
 *
 *  RETURN:     fPtr (open given file name with given mode)
 *                  || NULL if couldn't open the file)
 *
 */
FILE* reopenCurrentFileStream(char* sFileName, const char* mode, FILE* fPtr) {
	if (fPtr) { // close file if previous session opened opened?
		
	}
    
	// open file with given filemode
	fPtr = fopen(sFileName, mode);
	if (!fPtr) {
		printf(ERR_COULD_NOT_REOPEN_FILE(sFileName, mode));
	}
    
	return fPtr;
}

/*
 *  _openLastSessionFileStream
 *  LastSessionManager discovers backup file if exits
 *  and prompts user if he/she wishes to keep
 *
 *  PRE:        none
 *
 *  POST:       retrieves desired user name from user
 *              && prompts user whether he/she wishes to discard or not
 *
 *  RETURN:     fPtr (backup file pointer if backup file exists and user wishes to keep
 *                  || NULL if couldn't open the backup file)
 *
 */
static FILE* _openLastSessionFileStream(char* usFileName) {
	FILE* fPtr;             // file pointer for input stream
	char *usBacFileName;    // unsafe backup filename
    
	usBacFileName = _addFileExtension(usFileName, BACKUP_FILENAME_EXTENSION);
	fPtr = fopen(usBacFileName, FILEMODE_READONLY);
	if (NULL != fPtr) { /* if backup file opened */
		printf(VERB_LAST_SESSION_FOUND);
		fPtr = _promptDiscardLastSession(fPtr);
	}
	return fPtr;
}

/*
 *  _promptDiscardLastSession
 *  _promptDiscardLastSession asks user if he/she wants to discard
 *  saved backup file from which given file name.
 *
 *  PRE:        none
 *
 *  POST:       prompts user if he/she wants to discard backup file
 *
 *  RETURN:     fPtr (NULL if user discarded the last session
 *                  || backup file pointer; readonly; )
 *
 */
static FILE* _promptDiscardLastSession(FILE* fPtr) {
	input_value valueKey = INPUT_VALUE_INVALID;
    
	// prompt: do you wish to discard?
	valueKey = promptUserSelection(INPUT_TYPE_FILENAME, MSG_PROMPT_FILENAME);
    
	switch (valueKey) {
        case INPUT_VALUE_QUIT:
            exitOnUserRequest(EXIT_ON_USER_REQUEST);
            break;
        case INPUT_VALUE_NO:  // do not discard: last session
            return fPtr;
            break;
        case INPUT_VALUE_YES: // discard: last session
            fclose(fPtr);
            /* re-assignation of file pointer in case problem occurs
             * in case `fclose(fPtr)` returns error
             */
            fPtr = NULL;
            break;
        default:
            return NULL;
            break;
	}
    
	return fPtr;
}

/*
 *  _addFileExtension
 *  _addFileExtension adds file extension
 *  immediately after the originally given file name from user
 *
 *  PRE:        name (user-entered file name)
 *              extension (extension to be added after the file name)
 *
 *  POST:       adds file extension to the original file name
 *
 *  RETURN:     sName (validted modified file name with extension)
 *
 */
static char* _addFileExtension(char *name, const char *extension) {
	char *sName;        // safe name
    
    sName = malloc(strlen(name) + strlen(extension) + 1);
	// get: backup filename
	strcpy(sName, name);
    //don't free, it is used later.
	//free(name); // free safe input file name
	strcat(sName, BACKUP_FILENAME_EXTENSION);
    
	return sName;
}

/*
 *  _getNumberOfLines
 *  counts number of lines from the input file
 *
 *  PRE:    fPtr (input file pointer)
 *
 *  POST:   counts number of lines from the input file
 *
 *  RETURN: i (number of lines)
 *
 */

static int _getNumberOfLines(FILE* fPtr) {
	int i = 0;
    
<<<<<<< Updated upstream
	printf(VERB_GET_NUMBER_OF_LINES);
    
	while (EOF != fgetc(fPtr)) {
		while (fgetc(fPtr) != '\n')
			;
		i++;
	}
    
	return i;
}
=======
    return sInput;
}

bool saveQueue(const char *fname, QUEUE *que) { 

}

>>>>>>> Stashed changes
