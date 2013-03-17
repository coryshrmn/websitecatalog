/*
 * FileManager.c
 * FileManager.c contains necesary information with
 * current and last session management
 *
 * Developer:       Gon Kim (imgonkim@gmail.com)
 * Initial Commit:  03162013_221816
 * Last Updated:    03162013_221816
 *
 */
#include "../header/WebsiteCatalog.h"
#include "../header/constants.h"
#include "../header/FileManager.h"

FILE* CurrentSessionManager(const char* name, const char* mode, FILE* fPtr) {
	char *usFileName;   // unsafe filename
	char *sFileName;    // safe filename
	input_value valueKey = INPUT_VALUE_INVALID; // key for input value
    
	if (NULL != fPtr) {
		do {
			usFileName = _retrieveFileName(MSG_PROMPT_FILENAME);
			fPtr = _openFile(usFileName, mode);
			if (!fPtr) {
				printf(ERR_COULD_NOT_OPEN_FILE(usFileName));
				free(usFileName);
			}
		} while (!fPtr);
	} else {    /* reopens file with different mode */
		freopen(name, mode, fPtr);
		if (!fPtr) { /* if reopened successfully */
			printf(VERB_FILE_REOPEN(name, mode));
		} else {
			printf(ERR_COULD_NOT_REOPEN_FILE(name));
            exit(EXIT_FILE_NOT_OPENED);
        }
	}
	return fPtr;
}

/*
 *  LastSessionManager
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
FILE* LastSessionManager(void) {
	FILE* fPtr;             // file pointer for input stream
	char *usFileName;       // unsafe file name
	char *usBacFileName;    // unsafe backup filename
	char *sbacFileName;     // safe backup filename
	input_value valueKey = INPUT_VALUE_INVALID; // key for input value
    
	usFileName = _retrieveFileName(MSG_PROMPT_FILENAME);
	usBacFileName = _addFileExtension(usFileName, BACKUP_FILENAME_EXTENSION);
	fPtr = _openFile(usBacFileName, FILEMODE_READONLY);
	if (!fPtr) { /* if file does not exist */
		printf(ERR_COULD_NOT_OPEN_FILE(usBacFileName));
	} else {
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
	valueKey = getUserSelection(INPUT_TYPE_FILENAME, MSG_PROMPT_FILENAME);
    
	switch (valueKey) {
        case INPUT_VALUE_QUIT:
            exitOnUserRequest(EXIT_ON_USER_REQUEST);
            break;
        case INPUT_VALUE_NO:  // do not discard: last session
            return fPtr;
            break;
        case INPUT_VALUE_YES: // discard: last session
            fclose(fPtr);
            printf(VERB_LAST_SESSION_DISCARDED);
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
	char *sUserInput;   // safe user input
	int validKey;
    
	MALLOC(sName);
	// get: backup filename
	strcpy(sName, name);
	free(name); // free safe input file name
	strcat(sName, BACKUP_FILENAME_EXTENSION);
    
	return sName;
}

/*
 *  _retrieveFileName
 *  _retrieveFileName gets file name from user's stdio
 *
 *  PRE:    msg (prompt message at the time of retreiving user file name)
 *
 *  POST:   retrieves file name from the user
 *          && validate the input
 *
 *  RETURN: sInput (validated user-entered filename)
 *
 */
static char* _retrieveFileName(const char *msg) {
	char usInput[MAX_LENGTH_INPUT];                 // unsafe user input string
	input_value valueKey = INPUT_VALUE_INVALID;     // input value key
	const input_type type = INPUT_TYPE_FILENAME;    // input type
	char *sInput;                                   // safe user input string
    
	MALLOC(sInput);
	do {
		printf("%s", msg); // prompt message
		fgets(usInput, MAX_LENGTH_INPUT, stdin);
        
		// trim: '\n'
		usInput[strlen(usInput) - 1] = '\0';
        
		// validate: user input
		valueKey = ValidateManager(type, usInput);
		if (INPUT_VALUE_VALID == valueKey) {
			strcpy(sInput, usInput);
			return sInput;
		} else if (INPUT_VALUE_QUIT == valueKey) {
			exitOnUserRequest(EXIT_ON_REQUEST);
		}
	} while (INPUT_VALUE_INVALID == valueKey);
    
	return sInput;
}

/*
 *  _openFile 
 *  _openFile opens the file with given filename and mode 
 *
 *  PRE:        name (file name)
 *              mode (file mode)
 *
 *  POST:       opens file with given filename and mode
 *
 *  RETURN:     fPtr (NULL if couldn't open the file
 *                    valid file stream if opened successfully)
 *
 */
static FILE* _openFile(const char *name, const char *mode) {
	FILE* fPtr; // file pointer
	char *usFileName = NULL; // unsafe filename
    
	// fileopen: user-chosen input file's backup
	fPtr = fopen(name, mode);
	if (!fPtr) { /* if file does not exist */
		free(usFileName); // free: useless filename
	}
    
	return fPtr;
}

