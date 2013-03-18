/*
 * ValidateManager.c
 * contains ValidateManager and validates:
 *      (1) file input
 *      (2) user input from stdio.
 *     
 * Developer:           Gon Kim (imgonkim@gmail.com)
 * Initial Commit:      03162013_190139
 * Last Major Update:   03162013_190139
 * 
 */
#include "../header/WebsiteCatalog.h"
#include "../header/ValidateManager.h"

/*
 * validateInput
 * validates input (either file input or user input)
 *
 *  PRE:    type (input type)
 *          usInput (unsafe user-input to be validated
 *                   && doesn't contain newline character)
 *
 *  POST:   validate user input with given input type
 *
 *  RETURN:  INPUT_VALUE_INVALID (if user input is invalid)
 *          INPUT_VALUE_VALID (if user input is valid)
 *
 */
input_value validateInput(input_type type, char* usInput) {
	char usInputBuffer[MAX_LENGTH_INPUT];
	int (*validate)(char *usBuffer, const int len);
	int len = 0; // input length
	int i = 0;
	bool isLengthValid = false;
    
	// copy: raw input to buffer to work within ValidateManager
	strcpy(usInputBuffer, usInput);
    
	// get: length of unsafe input buffer
	len = strlen(usInputBuffer);
    
	// convert: lower case letters to upper case
	for (i = 0; i < len; i++) {
		usInputBuffer[i] = toupper(usInputBuffer[i]);
	}
    
	// validate: length of the input
	// && set: validating function per type
	switch (type) {
        case INPUT_TYPE_URL:
            isLengthValid = (INPUT_LENGTH_URL >= len);
            validate = _valUrl;
            break;
            
        case INPUT_TYPE_COMPANY:
            isLengthValid = (INPUT_LENGTH_COMPANY >= len);
            validate = _valCompany;
            break;
            
        case INPUT_TYPE_DAILY_PAGE_VIEW:
            isLengthValid = (INPUT_LENGTH_DAILY_PAGE_VIEW >= len);
        case INPUT_TYPE_RANK_TRAFFIC:
            isLengthValid = (INPUT_LENGTH_RANK_TRAFFIC >= len);
        case INPUT_TYPE_BACK_LINK:
            isLengthValid = (INPUT_LENGTH_BACK_LINK >= len);
        case INPUT_TYPE_WEBSITE_WORTH:
            isLengthValid = (INPUT_LENGTH_WEBSITE_WORTH >= len);
            validate = _valLongLongInt;
            break;
            
        case INPUT_TYPE_FILENAME:
            isLengthValid = (INPUT_LENGTH_FILENAME >= len);
            validate = _valFileName;
            break;
            
        case INPUT_TYPE_EXIT_ON_INVALID_FIELD:
            isLengthValid = (INPUT_LENGTH_EXIT_ON_INVALID_FIELD == len);
            validate = _valExitOnInvalidField;
            break;
            
        case INPUT_TYPE_RECONFIRM:
            isLengthValid = (INPUT_LENGTH_RECONFIRM == len);
        case INPUT_TYPE_DISCARD:
            isLengthValid = (INPUT_LENGTH_DISCARD == len);
            validate = _valYesOrNo;
        case INPUT_TYPE_MENU:
            isLengthValid = (INPUT_LENGTH_MENU == len);
            validate = _valMenuOption;
            break;
	}
	return isLengthValid ? validate(usInputBuffer, len) : INPUT_VALUE_INVALID;
}

/*
 * _valUrl
 *
 *  PRE:    usInput (unsafe user input)
 *          len (length of the input)
 *
 *  POST:   validate if input is in correct format of Url.
 * RETURN:  INPUT_VALUE_INVALID (if user input is invalid)
 *          INPUT_VALUE_VALID (if user input is valid)
 *
 */
static input_value _valUrl(char *usInput, const int len) {
	int i = 0;
    
	// TODO: convert to DELIMITER_URL
	while ((isalnum(usInput[i]) || DELIMITER_DOT == usInput[i])) {
		i++;
	}
    
	return len == i ? INPUT_VALUE_VALID : INPUT_VALUE_INVALID;
}

/*
 *  _valCompany
 *
 *  PRE:    usInput (unsafe user input)
 *          len (length of the input)
 *
 *  POST:   validate if input is in correct format of company name.
 *  RETURN: INPUT_VALUE_INVALID (if user input is invalid)
 *          INPUT_VALUE_VALID (if user input is valid)
 *
 */
static input_value _valCompany(char *usInput, const int len) {
	int i = 0;
    
	while ((isdigit(usInput[i]) || ispunct(usInput[i])) && len > i) {
		i++;
	}
    
	return len == i ? INPUT_VALUE_VALID : INPUT_VALUE_INVALID;
}

/*
 *  _valLongLongInt
 *
 *  PRE:    usInput (unsafe user input)
 *          len (length of the input)
 *
 *  POST:   validate if input is in correct format of long long int.
 *  RETURN: INPUT_VALUE_INVALID (if user input is invalid)
 *          INPUT_VALUE_VALID (if user input is valid)
 *
 */
static input_value _valLongLongInt(char *usInput, const int len) {
	int i = 0;
    
	while (0 <= usInput[i] && isdigit(usInput[i]) && len > i) {
		i++;
	}
    
	return len == i ? INPUT_VALUE_VALID : INPUT_VALUE_INVALID;
}

/*
 *  _valFilename
 *
 *  PRE:    usInput (unsafe user input)
 *          len (length of the input)
 *
 *  POST:   validate if input is in correct format of long long int.
 *
 *  RETURN: INPUT_VALUE_INVALID (if user input is invalid)
 *          INPUT_VALUE_VALID (if user input is valid)
 *
 */
static input_value _valFileName(char *usInput, const int len) {
	int i = 0;
    
	while ((isalnum(usInput[i]) || DELIMITER_DOT == usInput[i]) // TODO: replace with DELIMITER_URL
           && len > i) {
		i++;
	}
    
	return len == i ? INPUT_VALUE_VALID : INPUT_VALUE_INVALID;
}

/*
 *  _valExitOnInvalidField
 *
 *  PRE:    usInput (unsafe user input)
 *          len (length of the input)
 *
 *  POST:   validate if input is in correct format of response to
 *          exit on invalid field prompt.
 *
 *  RETURN: INPUT_VALUE_INVALID (if user input is invalid)
 *          INPUT_VALUE_VALID (if user input is valid)
 *
 */
static input_value _valExitOnInvalidField(char *usInput, const int len) {
	switch (usInput[0]) {
        case (INPUT_VALUE_QUIT_RAW):
            return INPUT_VALUE_QUIT;
            break;
        case (INPUT_VALUE_IGNORE_RAW):
            return INPUT_VALUE_IGNORE;
            break;
        case (INPUT_VALUE_IGNORE_ALL_RAW):
            return INPUT_VALUE_IGNORE_ALL;
            break;
        default:
            return INPUT_VALUE_INVALID;
	}
}

/*
 *  _valYesOrNo
 *
 *  PRE:    usInput (unsafe user input)
 *          len (length of the input)
 *
 *  POST:   validate if input is in correct format of yes or no prompt.
 *
 *  RETURN: INPUT_VALUE_INVALID (if user input is invalid)
 *          INPUT_VALUE_VALID (if user input is valid)
 *
 */
static input_value _valYesOrNo(char *usInput, const int len) {
	switch (usInput[0]) {
        case (INPUT_VALUE_QUIT_RAW):
            return INPUT_VALUE_QUIT;
            break;
        case (INPUT_VALUE_YES_RAW):
            return INPUT_VALUE_YES;
            break;
        case (INPUT_VALUE_NO_RAW):
            return INPUT_VALUE_NO;
            break;
        default:
            return INPUT_VALUE_INVALID;
	}
}

/*
 *  _valMenuOption
 *
 *  PRE:    usInput (unsafe user input)
 *          len (length of the input)
 *
 *  POST:   validate if input is in correct format of menu option
 *
 *  RETURN: INPUT_VALUE_INVALID (if user input is invalid)
 *          INPUT_VALUE_VALID (if user input is valid)
 * 
 */
static input_value _valMenuOption(char *usInput, const int len) {
	const int usMenu = usInput[0] - DELIMITER_ZERO;
    
	switch (usMenu) {
        case (INPUT_VALUE_QUIT_RAW):
            return INPUT_VALUE_QUIT;
        case MENU_TYPE_ADD_DATA:
        case MENU_TYPE_DELETE_DATA:
        case MENU_TYPE_FIND_KEY:
        case MENU_TYPE_PRINT_HASH:
        case MENU_TYPE_PRINT_SORTED_SEQUENCE:
        case MENU_TYPE_PRINT_INDENTED_TREE:
        case MENU_TYPE_SAVE:
        case MENU_TYPE_PRINT_EFFICIENCY:
        case MENU_TYPE_SAVE_AND_QUIT:
            return INPUT_VALUE_VALID;
            break;
        default:
            return INPUT_VALUE_INVALID;
            break;
	}
}
