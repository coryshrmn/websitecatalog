//
//  InputManager.c
//  websitecatalog
//
//  Created by Anonymous on 3/18/13.
//  Copyright (c) 2013 Anonymous. All rights reserved.
//

#include "WebsiteCatalog.h"
#include "InputManager.h"


/*******************************************************************************
 * Copies a string as lower case.
 *
 *    Pre: source is the original string
 *         dest is long enough to hold the original string
 *
 *   Post: dest is the lowercase version of source, with '\0' terminator.
 *
 * Return: --
 ******************************************************************************/
input_value getUserSelection(input_type type, const char *msg) {
	char usInput[MAX_LENGTH_INPUT];
	input_value value = INPUT_VALUE_INVALID;
    
	do {
		printf("%s", msg);
		fgets(usInput, MAX_LENGTH_INPUT, stdin);
        
		// trim: '\n'
		usInput[strlen(usInput) - 1] = '\0';
        
		// validate: user input
		value = validateInput(type, usInput);
		if (INPUT_VALUE_QUIT == value) {
			exit(EXIT_ON_USER_REQUEST);
		}
	} while (INPUT_VALUE_INVALID == value);
	return value;
}

/*
 *  promptSingleField
 *  reads one field from the line per given input type. Then,
 *  returns the validated field
 *
 *  PRE:    type (input type)
 *          msg (prompt message for input)
 *
 *  POST:   gets one field from the buffer line
 *          calls ValidateManager for validation purposes
 *
 *  RETURN: usField (string type of parsed & validated field)
 *
 */
void* promptSingleField(input_type type, const char *msg) {
    char *usField;          // unsafe field string (processed from `line`)
    input_value validKey;    // input value validity
    
    MALLOC(usField);
    do {
        printf("%s", msg);
        fgets(usField, MAX_LENGTH_INPUT, stdin);
        
		// trim: '\n'
		usField[strlen(usField) - 1] = '\0';
        
        // validate: single field from the line
        validKey = validateInput(type, usField);
        switch (validKey) {
            case INPUT_VALUE_QUIT:
                exitOnUserRequest(EXIT_ON_USER_REQUEST);
                break;
            case INPUT_VALUE_INVALID:
                // free: invalid field read
                free(usField);
            case INPUT_VALUE_VALID:
                break;
        }
    } while (INPUT_VALUE_INVALID == validKey);
    
    return usField;
}


/*
 *  readOneLine
 *  reads one line from the input file stream.
 *
 *  PRE:    fPtr (file pointer; readonly; from input file stream)
 *
 *  POST:   read one line from the buffer
 *          excludes delimiter from the buffer string
 *
 *  RETURN: sBuffer (buffer line read from the input file stream)
 *
 */
char* readOneLine(FILE* fPtr) {
	int numCharRead = 0;                    // number of characters read
	char usBuffer[MAX_LENGTH_INPUT];        // unsafe buffer  string
	char *sBuffer;                           // safe buffer string
    
	// read: until linebreak or EOF is read
	usBuffer[numCharRead] = fgetc(fPtr);
	if (EOF != usBuffer[numCharRead]) {
		while ('\n' != usBuffer[numCharRead]) {
			numCharRead++;
			usBuffer[numCharRead] = fgetc(fPtr);
		}
	} else {
		return NULL; // reached EOF
	}
    
	// exclude: delimiter from bufferString
	usBuffer[numCharRead] = '\0';
    
	// dynamically allocate: bufferString
	sBuffer = malloc(strlen(usBuffer) + 1);
	if (!sBuffer) {
        exit(EXIT_NOT_ENOUGH_MEMORY);
    }
    
    // copy: unsafe buffer to safe buffer
    strcpy(sBuffer, usBuffer);
	return sBuffer;
}

/*
 *  readSingleField
 *  reads one field from the line per given input type. Then,
 *  returns the validated field
 *
 *  PRE:    type (input type)
 *          line (buffer input line)
 *
 *  POST:   locate one delimiter;
 *          parses one field from the buffer line
 *          calls ValidateManager for validation purposes
 *
 *  RETURN: usField (string type of parsed & validated field)
 *
 */
void* readSingleField(input_type type, char **line) {
    char *usField;          // unsafe field string (processed from `line`)
    char *loc;              // location of the delimiter
    int i;                  // iterating variable
    
    MALLOC(usField);
    // locate: delimiter
    loc = strchr(*line, DELIMITER_SEMICOLON);
    
    // update the location of the stirng pointer
    for(i = 0; i < loc - *line; i++) {
        usField[i] = (*line)[i];
    }
    
    *line = loc + 1;
    
    // validate: single field from the line
    if (INPUT_VALUE_VALID == validateInput(type, usField)) {
        return usField;
    } else {
        // free: invalid field read
        free(usField);
        return NULL;
    }
}

/*
 *  retrieveFileName
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
char* retrieveFileName(const char *msg) {
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
        valueKey = validateInput(type, usInput);
        if (INPUT_VALUE_VALID == valueKey) {
            strcpy(sInput, usInput);
            return sInput;
        } else if (INPUT_VALUE_QUIT == valueKey) {
            exitOnUserRequest(EXIT_ON_USER_REQUEST);
        }
    } while (INPUT_VALUE_INVALID == valueKey);
    
    return sInput;
}