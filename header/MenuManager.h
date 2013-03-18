/*
 * MenuManager.h
 * contains menu-related functions.
 *
 * Developer:           Gon Kim (imgonkim@gmail.com)
 * Initial Commit:      03172013_030344
 * Last Major Update:   03162013_055555
 *
 */
// project.main.MenuManager.CONSTANT_DEFINED
#define MSG_PROMPT_MENU_SELECTION               "Choose menu (1-9): "
#define MSG_PROMPT_TO_SAVE                      "Save current session to same file (Y/N)? "
#define MSG_PROMPT_TO_SAVE_AS                   "Enter file name to save current session: "

#define MSG_PROMPT_URL                          "Enter Url: "
#define MSG_PROMPT_COMPANY                      "Enter Company Name: "             
#define MSG_PROMPT_DAILY_PAGE_VIEW              "Enter Daily Page View: "
#define MSG_PROMPT_RANK_TRAFFIC                 "Enter Traffic Rank: "
#define MSG_PROMPT_MENU_BACK_LINK               "Enter Back Links: "
#define MSG_PROMPT_MENU_WEBSITE_WORTH           "Enter Website Worth in USD: "
#define MSG_PROMPT_QUIT                         "Do you wish to quit program? (Y/N)? "


#define VERB_DATA_NOT_MODIFIED(name)            ">VERBOSE : Data is not modified. \
No changes has been made to file \"%s\".\n", name
#define VERB_QUIT_FROM_MENU                     ">VERBOSE : Exiting Program...\n" 
#define VERB_LIST_DELETE(key)                   ">VERBOSE : Deleted \"%s\" from the list\n", key
#define VERB_LIST_FOUND(key)                    ">VERBOSE : Found \"%s\" from the list\n", key

#define WARN_KEY_NOT_FOUND(key)                ">>WARNING: \"%s\" is not found from the list.\n", key

#define ERR_INVALID_MENU                        ">>>ERROR : Invalid menu selection. Please try again.\n"
#define ERR_NOT_SAVED                           ">>>ERROR : Unable to save current session.\n"
#define ERR_UNABLE_TO_QUIT_FROM_MENU            ">>>ERROR : Unable to quit program from menu.\n"

// project.main.MenuManager.CONSTANT_STRING
const char* menu_msg[] = { /* captions for each menu option */
    /* 0 */"INVALID MENU TYPE",
    /* 1 */"Add: new Website",
    /* 2 */"Delete: Website",
    /* 3 */"Search and Print: Website using its URL",
    /* 4 */"Print: List of Websites in hash table sequence",
    /* 5 */"Print: List of Websites in key sequence (sorted)",
    /* 6 */"Print: List of Websites in indented tree",
    /* 7 */"Print: Efficiency statistics",
    /* 8 */"Save",
    /* 8 */"Save As...",
    /* 9 */"Quit"
};

// project.main.MenuManager.PRIVATE_FUNCTION_DELCARATIONS
static void _printMenu();
static menu_type _promptMenu(void);
static menu_type _getMenuSelection(void);

/*
 *  _addDataFromMenu
 *  prompts user to add Website info.
 *
 *  PRE:        head (list header)
 *
 *  POST:       prompt user to add Website info.
 *
 *  RETURN:     true if successfully inserted
 *              false if failed.
 *
 */
static bool _addDataFromMenu(ListHead *head);
static bool _deleteDataFromMenu(ListHead *head);
static bool _findKeyFromMenu(ListHead *head);
static void _printHashFromMenu(ListHead *head);
static void _printSortedSequenceFromMenu(ListHead *head);
static void _printIndentedTreeFromMenu(ListHead *head);
static void _printEfficiencyFromMenu(ListHead *head);
static FILE* _saveFromMenu(ListHead *head, FILE *fPtr, char* sFileName, bool isDataModified);

static void _saveAsFromMenu(ListHead *head, FILE** fPtr, char **sFileName);
static bool _quitFromMenu(ListHead *head, FILE* fPtr, char *sFileName, bool isDataModified);

