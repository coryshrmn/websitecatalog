/*
 * ValidateManager.h
 *
 * Developer: Gon Kim (imgonkim@gmail.com
 */
// project.main.ValidateManager.CONSTANT_DEFINED.delimiter
#define DELIMITER_URL "./"
#define DELIMITER_DOT '.'
#define DELIMITER_ZERO '0'
#define DELIMITER_UNDERSCORE '_'
#define DELIMITER_DASH       '-'
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
