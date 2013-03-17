/*
 * MenuManager.h
 * contains menu-related functions.
 *
 * Developer:           Gon Kim (imgonkim@gmail.com)
 * Initial Commit:      03172013_030344
 * Last Major Update:   03162013_055555
 *
 */
// project.constants.MSG
const char* menu_msg[] = { /* captions for each menu option */
    /* 0 */"DUMMY MENU MESSAGE", // TODO: explain why dummy menu exists (for UI)
    /* 1 */"Add: new Website",
    /* 2 */"Delete: Website",
    /* 3 */"Search and Print: Website using its URL",
    /* 4 */"Print: List of Websites in hash table sequence",
    /* 5 */"Print: List of Websites in key sequence (sorted)",
    /* 6 */"Print: List of Websites in indented tree",
    /* 7 */"Save: Modified Website info to a file"
    /* 8 */"Print: Efficiency statistics"
};

static void _printMenu();
static menu_type _chooseMenu(void);