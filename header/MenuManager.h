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
#define MSG_PROMPT_MENU_SELECTION               "Choose menu (1-9): "

#define MSG_PROMPT_URL                          "Enter Url: "
#define MSG_PROMPT_COMPANY                      "Enter Company Name: "             
#define MSG_PROMPT_DAILY_PAGE_VIEW              "Enter Daily Page View: "
#define MSG_PROMPT_RANK_TRAFFIC                 "Enter Traffic Rank: "
#define MSG_PROMPT_MENU_BACK_LINK               "Enter Back Links: "
#define MSG_PROMPT_MENU_WEBSITE_WORTH           "Enter Website Worth in USD: "

#define ERR_INVALID_MENU                       ">>>ERROR : Invalid Menu. \
Please try again.\n"

// project.main.MenuManager.CONSTANT_STRING
const char* menu_msg[] = { /* captions for each menu option */
    /* 0 */"INVALID MENU TYPE",
    /* 1 */"Add: new Website",
    /* 2 */"Delete: Website",
    /* 3 */"Search and Print: Website using its URL",
    /* 4 */"Print: List of Websites in hash table sequence",
    /* 5 */"Print: List of Websites in key sequence (sorted)",
    /* 6 */"Print: List of Websites in indented tree",
    /* 7 */"Save: Modified Website info to a file",
    /* 8 */"Print: Efficiency statistics",
    /* 9 */"Save and Quit Program"
};

// project.main.MenuManager.PRIVATE_FUNCTION_DELCARATIONS
static void _printMenu();
static menu_type _chooseMenu(void);
static menu_type _getMenuSelection(void);

static bool _addDataFromMenu(ListHead *head);
static bool _deleteDataFromMenu(ListHead *head);
static bool _findKeyFromMenu(ListHead *head);
static bool _printHashFromMenu(ListHead *head);
static bool _printSortedSequenceFromMenu(ListHead *head);
static bool _printIndentedTreeFromMenu(ListHead *head);
static bool _saveSessionFromMenu(ListHead *head, FILE *fPtr);
static bool _printEfficiencyFromMenu(ListHead *head);
static bool _saveAndQuitFromMenu(FILE *fPtr);

