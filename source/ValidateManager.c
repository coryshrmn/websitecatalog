/*******************************************************************************
 * ValidateManager.c
 * contains ValidateManager and validates:
 *      (1) file input
 *      (2) user input from stdio.
 *
 * Developer(s):
 * 		Gon Kim			(imgonkim@gmail.com)
 * 		Cory Sherman	(coryshrmn@gmail.com)
 *
 * Contains functions for validating user input.
 *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "WebsiteCatalog.h"

// project.main.ValidateManager.CONSTANT_DEFINED.inputLength
#define INPUT_LENGTH_URL                    MAX_LENGTH_INPUT
#define INPUT_LENGTH_COMPANY                MAX_LENGTH_INPUT

// 13 digits are less than one trillion
#define INPUT_LENGTH_DAILY_PAGE_VIEW        13
#define INPUT_LENGTH_RANK_TRAFFIC           13
#define INPUT_LENGTH_BACK_LINK              13
#define INPUT_LENGTH_WEBSITE_WORTH          13
#define INPUT_LENGTH_FILENAME               MAX_LENGTH_INPUT
#define INPUT_LENGTH_EXIT_ON_INVALID_FIELD  1
#define INPUT_LENGTH_RECONFIRM              1
#define INPUT_LENGTH_DISCARD                1
#define INPUT_LENGTH_MENU                   1
#define INPUT_LENGTH_EXIT_ON_INVALID_FIELD  1
#define INPUT_LENGTH_YES_OR_NO              1
#define INPUT_LENGTH_SAVE                   1
#define INPUT_LENGTH_SAVE_AS                MAX_LENGTH_INPUT
#define INPUT_LENGTH_QUIT                   1

// project.main.ValidateManager.CONSTANT_DEFINED.inputValue
#define INPUT_VALUE_QUIT_RAW                'q'
#define INPUT_VALUE_IGNORE_RAW              'i'
#define INPUT_VALUE_IGNORE_ALL_RAW          'a'
#define INPUT_VALUE_YES_RAW                 'y'
#define INPUT_VALUE_NO_RAW                  'n'

// project.main.validateManager.CONSTANT_DEFINED.delimiter
#define DELIMITER_SPACE                         ' '
#define DELIMITER_SEMICOLON                     ';'
#define DELIMITER_NEWLINE                       '\n'
#define DELIMITER_SLASH                         '/'
#define DELIMITER_DOT                           '.'
#define DELIMITER_ZERO                          '0'
#define DELIMITER_UNDERSCORE                    '_'
#define DELIMITER_DASH                          '-'

// project.main.ValidateManager.CONSTANT_DEFINED.error
#define ERR_INVALID_INPUT_TYPE ">>>ERROR: Invalid input type.\n"

// project.main.ValidateManager.PRIVATE_FUNCTION_DECLARATIONS.fileInputValidation
static bool _valFileName(char *usInput, size_t len);
static bool _valUrl(char *usInput, size_t len);
static bool _valCompany(char *usInput, size_t len);
static bool _valLongLongInt(char *usInput, size_t len);

// project.main.ValidateManager.PRIVATE_FUNCTION_DECLARATIONS.userInputValidation
static bool _valExitOnInvalidField(char *usInput, size_t len);
static bool _valYesOrNo(char *usInput, size_t len);
static bool _valMenuOption(char *usInput, size_t len);

/*******************************************************************************
 * Validates input (either file input or user input)
 *
 *     Pre: type (input type)
 *          usInput (unsafe user-input to be validated
 *                   && doesn't contain newline character)
 *
 *    Post: validate user input with given input type
 *
 *  Return: false (if user input is invalid)
 *          true (if user input is valid)
 *
 ******************************************************************************/
bool validateInput(input_type type, char* usInput) {
	char usInputBuffer[MAX_LENGTH_INPUT];
	bool (*validate)(char *usBuffer, const unsigned long len);
	size_t len = 0; // input length
	int i = 0;
	bool isLengthValid = false;

	// copy: raw input to buffer to work within ValidateManager
	strcpy(usInputBuffer, usInput);

	// count: input string length
	len = strlen(usInputBuffer);

	if (0l == len) {
		return false;
	}

	// convert: lower case letters to upper case
	for (i = 0; i < len; i++) {
		usInputBuffer[i] = tolower(usInputBuffer[i]);
	}

	// validate: length of the input
	// && set: validating function per type
	switch (type) {
	/*
	 * The following case(s) return true
	 * only if the input is one of the following:
	 *
	 * alphanumeric characters
	 * period(".")
	 *
	 */
	case INPUT_TYPE_URL:
		isLengthValid = (INPUT_LENGTH_URL >= len);
		validate = _valUrl;
		break;

		/*
		 * The following case(s) return true
		 * only if the input is one of the following:
		 *
		 * alphanumeric characters
		 * space
		 * punctuation
		 *
		 */
	case INPUT_TYPE_COMPANY:
		isLengthValid = (INPUT_LENGTH_COMPANY >= len);
		validate = _valCompany;
		break;

		/*
		 * The following case(s) return true
		 * only if the input is one of the following:
		 *
		 *  positive integer less than one trillion
		 *
		 */
	case INPUT_TYPE_DAILY_PAGE_VIEW:
		isLengthValid = (INPUT_LENGTH_DAILY_PAGE_VIEW >= len);
		validate = _valLongLongInt;
		break;
	case INPUT_TYPE_RANK_TRAFFIC:
		isLengthValid = (INPUT_LENGTH_RANK_TRAFFIC >= len);
		validate = _valLongLongInt;
		break;
	case INPUT_TYPE_BACK_LINK:
		isLengthValid = (INPUT_LENGTH_BACK_LINK >= len);
		validate = _valLongLongInt;
		break;
	case INPUT_TYPE_WEBSITE_WORTH:
		isLengthValid = (INPUT_LENGTH_WEBSITE_WORTH >= len);
		validate = _valLongLongInt;
		break;

	case INPUT_TYPE_FILENAME:
		isLengthValid = (INPUT_LENGTH_FILENAME >= len);
		validate = _valFileName;
		break;
	case INPUT_TYPE_SAVE_AS:
		isLengthValid = (INPUT_LENGTH_SAVE_AS >= len);
		validate = _valFileName;
		break;
	case INPUT_TYPE_EXIT_ON_INVALID_FIELD:
		isLengthValid = (INPUT_LENGTH_EXIT_ON_INVALID_FIELD == len);
		validate = _valExitOnInvalidField;
		break;
		/*
		 * The following case(s) return true
		 * only if the input is one of the following:
		 * 'Y', 'y', 'N', 'n'
		 */
	case INPUT_TYPE_RECONFIRM:
		isLengthValid = (INPUT_LENGTH_RECONFIRM == len);
		validate = _valYesOrNo;
		break;
	case INPUT_TYPE_DISCARD:
		isLengthValid = (INPUT_LENGTH_DISCARD == len);
		validate = _valYesOrNo;
		break;
	case INPUT_TYPE_SAVE:
		isLengthValid = (INPUT_LENGTH_SAVE == len);
		validate = _valYesOrNo;
		break;
	case INPUT_TYPE_QUIT:
		isLengthValid = (INPUT_LENGTH_QUIT == len);
		validate = _valYesOrNo;
		break;
		/*
		 * The following case(s) return true
		 * only if the input is one of the following:
		 * 1, 2, 3, 4, 5, 6, 7, 8, 9
		 */
	case INPUT_TYPE_MENU:
		isLengthValid = (0 <= INPUT_LENGTH_MENU && 2 >= INPUT_LENGTH_MENU);
		validate = _valMenuOption;
		break;
	}

	if (!(isLengthValid && validate(usInputBuffer, len))) {
		printf(ERR_INVALID_INPUT);
		return false;
	}

	return true;
}

/*******************************************************************************
 * Validates Url.
 *
 *     Pre:  usInput (unsafe user input)
 *           len (length of the input)
 *
 *    Post:  validate if input is in correct format of Url.
 *  Return:  false (if user input is invalid)
 *           true (if user input is valid)
 *
 ******************************************************************************/
static bool _valUrl(char *usInput, size_t len) {
	int i = 0;
	bool isValid = false;

	/* (valid if true)      Does Url start with http://www. */
	if (0 == strncmp("http://www.", usInput, 11)) {
		i = 11;
	}

	/* (valid if true)      Does Url start with http://     */
	if (0 == strncmp("http://", usInput, 7)) {
		i = 7;
	}

	// (valid if true)      Does Url start with www.
	if (0 == strncmp("www.", usInput, 4)) {
		i = 4;
	}

	// (invalid if true)    Does Url start start with .
	if (usInput[0] == DELIMITER_DOT) {
		return false;
	}

	// (invalid if true)    Does Url ends with .
	if (usInput[len - 1] == DELIMITER_DOT) {
		return false;
	}

	// (invalid if true) Does the Url have at least one period within user input?
	while ((isalnum(usInput[i]) || DELIMITER_DOT == usInput[i])) {
		if (DELIMITER_DOT == usInput[i]) {
			isValid = true;
		}
		i++;
	}

	return isValid && len == i ? true : false;
}

/*******************************************************************************
 *  Validates company name.
 *
 *     Pre: usInput (unsafe user input)
 *          len (length of the input)
 *
 *    Post: validate if input is in correct format of company name.
 *  Return: false (if user input is invalid)
 *          true (if user input is valid)
 *
 ******************************************************************************/
static bool _valCompany(char *usInput, size_t len) {
	int i = 0;

	while ((isalnum(usInput[i]) || ispunct(usInput[i]) || isspace(usInput[i]))
			&& len > i) {
		i++;
	}

	return len == i ? true : false;
}

/*******************************************************************************
 *  Validates long long int.
 *
 *     Pre: usInput (unsafe user input)
 *          len (length of the input)
 *
 *    Post: validate if input is in correct format of long long int.
 *  Return: false (if user input is invalid)
 *          true (if user input is valid)
 *
 ******************************************************************************/
static bool _valLongLongInt(char *usInput, size_t len) {
	int i = 0;

	while (0 <= usInput[i] && isdigit(usInput[i]) && len > i) {
		i++;
	}

	return len == i ? true : false;
}

/*******************************************************************************
 *  Validates filename.
 *
 *     Pre: usInput (unsafe user input)
 *          len (length of the input)
 *
 *    Post: validate if input is in correct format of long long int.
 *
 *  Return: false (if user input is invalid)
 *          true (if user input is valid)
 *
 ******************************************************************************/
static bool _valFileName(char *usInput, size_t len) {
	int i = 1;

	// validate first chracter of the filename.
	// NOTE: first chracter of the file name should be alnum
	if (!isalnum(usInput[0])) {
		return false;
	}

	// validate the rest of the file name
	while ((isalnum(usInput[i]) || DELIMITER_DOT == usInput[i]
			|| DELIMITER_UNDERSCORE == usInput[i]
			|| DELIMITER_DASH == usInput[i]) && len > i) {
		i++;
	}

	return len == i ? true : false;
}

/*******************************************************************************
 *  Validates ignore/ignore all/quit option
 *
 *     Pre: usInput (unsafe user input)
 *          len (length of the input)
 *
 *    Post: validate if input is in correct format of response to
 *          exit on invalid field prompt.
 *
 *  Return: false (if user input is invalid)
 *          true (if user input is valid)
 *
 ******************************************************************************/
static bool _valExitOnInvalidField(char *usInput, size_t len) {
	switch (usInput[0]) {
	case (INPUT_VALUE_QUIT_RAW):
	case (INPUT_VALUE_IGNORE_RAW):
	case (INPUT_VALUE_IGNORE_ALL_RAW):
		return true;
		break;
	default:
		return false;
	}
}

/*******************************************************************************
 *  Validates Yes or No option.
 *
 *     Pre: usInput (unsafe user input)
 *          len (length of the input)
 *
 *    Post: validate if input is in correct format of yes or no prompt.
 *
 *  Return: false (if user input is invalid)
 *          true (if user input is valid)
 *
 ******************************************************************************/
static bool _valYesOrNo(char *usInput, size_t len) {
	switch (usInput[0]) {
	case (INPUT_VALUE_YES_RAW):
	case (INPUT_VALUE_NO_RAW):
	case (INPUT_VALUE_QUIT_RAW):
		return true;
		break;
	default:
		return false;
	}
}

/*******************************************************************************
 *  Validates menu option.
 *
 *     Pre: usInput (unsafe user input)
 *          len (length of the input)
 *
 *    Post: validate if input is in correct format of menu option
 *
 *  Return: false (if user input is invalid)
 *          true (if user input is valid)
 *
 ******************************************************************************/
static bool _valMenuOption(char *usInput, size_t len) {
	int usMenu = usInput[0] - DELIMITER_ZERO;

	switch (usMenu) {
	case MENU_INSERT:
	case MENU_DELETE:
	case MENU_SEARCH:
	case MENU_PRINT_HASH:
	case MENU_PRINT_INORDER:
	case MENU_PRINT_INDENTED:
	case MENU_PRINT_EFFICIENCY:
	case MENU_SAVE:
	case MENU_SAVE_AS:
	case MENU_QUIT:

		return true;
		break;
	default:
		return false;
		break;
	}
}
