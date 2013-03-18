/*
 * FileManager.c
 * FileManager.c contains necesary information regarding the file I/O
 * and last-session manager
 *
 * Developer:           Gon Kim (imgonkim@gmail.com)
 * Initial Commit:      03162013_221816
 * Last Major Update:   03172013_061039
 *
 */
// project.main.FileManager.CONSTANT_DEFINED
#define VERB_FILEOPEN(name, mode)               ">VERBOSE:  File \"%s\" is opened for %s mode.\n", name, mode
#define VERB_FILE_REOPEN(name, mode)            ">VERBOSE:  File \"%s\" is re-opening for mode \"%s\"", name, mode
#define VERB_LAST_SESSION_FOUND                 ">VERBOSE:  Last session was not saved.\n"
#define VERB_LAST_SESSION_DISCARDED             ">VERBOSE:  Last session was discarded.\n"
#define VERB_GET_NUMBER_OF_LINES                ">VERBOSE:  Counting number of lines.\n"

#define ERR_COULD_NOT_OPEN_FILE(filename)       ">>>ERROR : Could not open file, \"%s\".\n", filename
#define ERR_COULD_NOT_REOPEN_FILE(filename)     ">>>ERROR : Could not re-open file with different mode, \"%s\".\n", filename
#define ERR_FILE_NOT_OPENED                    ">>>ERROR : File could not be opened.\n"
#define ERR_FILE_NOT_CLOSED                    ">>>ERROR : File could not be closed.\n"

#define MSG_PROMPT_DISCARD                      "Discard last session(Y/N)? Enter \"Y\" to discard or \"N\" to load last session.\n"
#define MSG_PROMPT_FILENAME                     "Please enter filename: "
#define BACKUP_FILENAME_EXTENSION               ".bac"

// project.main.FileManager.PRIVATE_FUNCTION_DECLARATIONS
static FILE* _reopenLastSessionFileStream(const char* usFileName);
static FILE* _openLastSessionFileStream(char* usFileName);
static char* _retrieveFileName(const char *msg);
static char* _addFileExtension(char *name, const char *extension);
static FILE* _promptDiscardLastSession (FILE* fPtr);
static int _getNumberOfLines(FILE* fPtr);
