/*
 * ValidateManager.c
 * ValidateManager contains ValidateManager and validates:
 *      (1) file input
 *      (2) user input from stdio.
 *
 * Developer:           Gon Kim (imgonkim@gmail.com)
 * Initial Commit:      03162013_190139
 * Last Major Update:   03172013_015535
 *
 */
#include <ctype.h>
// project.main.ValidateManager.CONSTANT_DEFINED.delimiter
#define DELIMITER_URL "./"
#define DELIMITER_DOT '.'
#define DELIMITER_ZERO '0'
// project.main.ValidateManager.CONSTANT_DEFINED.inputLength
#define INPUT_LENGTH_URL                    MAX_LENGTH_INPUT
#define INPUT_LENGTH_COMPANY                MAX_LENGTH_INPUT
#define INPUT_LENGTH_DAILY_PAGE_VIEW        INT_MAX
#define INPUT_LENGTH_RANK_TRAFFIC           INT_MAX
#define INPUT_LENGTH_BACK_LINK              INT_MAX
#define INPUT_LENGTH_WEBSITE_WORTH          INT_MAX
#define INPUT_LENGTH_FILENAME               MAX_LENGTH_INPUT
#define INPUT_LENGTH_EXIT_ON_INVALID_FIELD  1
#define INPUT_LENGTH_RECONFIRM              1
#define INPUT_LENGTH_DISCARD                1
#define INPUT_LENGTH_MENU                   1
#define INPUT_LENGTH_EXIT_ON_INVALID_FIELD  1
#define INPUT_LENGTH_YES_OR_NO              1
// project.main.ValidateManager.CONSTANT_DEFINED.inputValue
#define INPUT_VALUE_QUIT_RAW                'Q'
#define INPUT_VALUE_IGNORE_RAW              'I'
#define INPUT_VALUE_IGNORE_ALL_RAW          'A'
#define INPUT_VALUE_YES_RAW                 'Y'
#define INPUT_VALUE_NO_RAW                  'N'
// project.main.ValidateManager.CONSTANT_DEFINED.error
#define ERR_INVALID_INPUT_TYPE ">>>ERROR: Invalid input type.\n"

// project.main.ValidateManager.PRIVATE_FUNCTION_DECLARATIONS.fileInputValidation
static input_value _valFileName(char *usInput, const int len);
static input_value _valUrl(char *usInput, const int len);
static input_value _valCompany(char *usInput, const int len);
static input_value _valLongLongInt(char *usInput, const int len);
// project.main.ValidateManager.PRIVATE_FUNCTION_DECLARATIONS.userInputValidation
static input_value _valExitOnInvalidField(char *usInput, const int len);
static input_value _valYesOrNo(char *usInput, const int len);
static input_value _valMenuOption(char *usInput, const int len);
