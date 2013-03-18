/*
 * constants.h
 * constants.h contains enum and defined constants
 *
 * Developer:           Gon Kim (imgonkim@gmail.com)
 * Initial Commit:      03162013_190139
 * Last Major Update:   03172013_015442
 *
 */
// project.main.CONSTANT_ENUM
typedef enum {
    INPUT_VALUE_INVALID = -1,           /* -1 */
    INPUT_VALUE_NO,                     /*  0 */
    INPUT_VALUE_YES,                    /*  1 */
    INPUT_VALUE_VALID,                  /*  2 */
    INPUT_VALUE_IGNORE,                 /*  3 */
    INPUT_VALUE_IGNORE_ALL,             /*  4 */
    INPUT_VALUE_QUIT                    /*  5 */
} input_value;

typedef enum {
	INPUT_TYPE_URL = 2001,              /* 2001 */
	INPUT_TYPE_COMPANY,                 /* 2002 */
	INPUT_TYPE_DAILY_PAGE_VIEW,         /* 2003 */
	INPUT_TYPE_RANK_TRAFFIC,            /* 2004 */
	INPUT_TYPE_BACK_LINK,               /* 2005 */
	INPUT_TYPE_WEBSITE_WORTH,           /* 2006 */
    
	INPUT_TYPE_FILENAME = 3001,         /* 3001 */
	INPUT_TYPE_EXIT_ON_INVALID_FIELD,   /* 3002 */
	INPUT_TYPE_RECONFIRM,               /* 3003 */
    INPUT_TYPE_DISCARD,                 /* 3004 */
    INPUT_TYPE_SAVE,                    /* 3005 */
    INPUT_TYPE_SAVE_AS,                 /* 3006 */
    INPUT_TYPE_QUIT,                    /* 3007 */
    
    INPUT_TYPE_MENU = 4001              /* 4001 */
} input_type;

typedef enum {
    MENU_TYPE_INVALID,                  /* 0 */
    MENU_TYPE_ADD_DATA,                 /* 1 */
    MENU_TYPE_DELETE_DATA,              /* 2 */
    MENU_TYPE_FIND_KEY,                 /* 3 */
    MENU_TYPE_PRINT_HASH,               /* 4 */
    MENU_TYPE_PRINT_SORTED_SEQUENCE,    /* 5 */
    MENU_TYPE_PRINT_INDENTED_TREE,      /* 6 */
    MENU_TYPE_PRINT_EFFICIENCY,         /* 7 */
    MENU_TYPE_SAVE,                     /* 8 */
    MENU_TYPE_SAVE_AS,                  /* 9 */
    MENU_TYPE_QUIT             /*10 */
} menu_type;

// project.main.CONSTANT_DEFINED
#define FILEMODE_READONLY                       "r"
#define FILEMODE_WRITE                          "w"
#define FILEMODE_OVERWRITE                      "w+"
#define HR  "================================================\n"
#define BR                                      "\n"
#define MSG_EXIT_SELECTION                      "Enter \"I\" to ignore once, \
                                                \"A\" to ignore all,         \
                                                or \"Q\" to quit program\n"
#define FLUSH while (getchar() != '\n');

#define MAX_LENGTH_INPUT                        255
#define MAX_LENGTH_DOB                          8
#define MAX_LENGTH_ID                           3
#define MAX_NUMBER_PERSON                       100
#define EXIT_NOT_ENOUGH_MEMORY                  101
#define EXIT_FILE_NOT_OPENED                    102
#define EXIT_FILE_NOT_CLOSED                    103
#define EXIT_FILE_NOT_WRITTEN                   104
#define EXIT_ON_USER_REQUEST                    105


#define ERR_COULD_NOT_CLOSE_FILE(name)          ">>>ERROR : Could not close file \"%s\".\n", name
#define ERR_COULD_NOT_OPEN_FILE(name)           ">>>ERROR : Could not open file, \"%s\".\n", name
#define ERR_COULD_NOT_REOPEN_FILE(name, mode)   ">>>ERROR : Could not re-open file \"%s\" with \"%s\" mode.\n", name, mode
#define ERR_NOT_ENOUGH_MEMORY                   ">>>ERROR : Not enough memory.\n"
#define ERR_INVALID_INPUT                       ">>>ERROR : Invalid input. \
                                                Please try again.\n"
#define WARN_ID_NOT_FOUND(type)                 ">>WARNING: %s is not found.\n", type

#define MSG_PROMPT_RECONFIRM                    "Are you sure?\n"

#define USERINPUT_QUIT                          "QUIT"
#define DELIMITER_SPACE                         ' '
#define DELIMITER_SEMICOLON                     ';'
#define DELIMITER_NEWLINE                       '\n'
#define DELIMITER_SLASH                         '/'

#define MALLOC(param)                 if (!(param = malloc(sizeof(*param)))) {\
printf(ERR_NOT_ENOUGH_MEMORY);\
exit(EXIT_NOT_ENOUGH_MEMORY);\
}

