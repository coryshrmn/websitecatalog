/*
 * FileManager.c
 * FileManager.c contains necesary information regarding the file I/O
 * and last-session manager
 *
 * Developer:       Gon Kim (imgonkim@gmail.com)
 * Initial Commit:  03162013_221816
 * Last Updated:    03162013_221816
 *
 */
// project.main.fileManager.CONSTANT_DEFINED
#define VERB_FILEOPEN(name, mode)              ">VERBOSE:  File \"%s\" is opened for %s mode.\n", name, mode
#define VERB_FILE_REOPEN(name, mode)           ">VERBOSE:  File \"%s\" is re-opening for mode \"%s\""
#define ERR_COULD_NOT_OPEN_FILE(filename)      ">>>ERROR : Could not open file, \"%s\".\n", filename
#define ERR_COULD_NOT_REOPEN_FILE(filename)      ">>>ERROR : Could not re-open file with different mode, \"%s\".\n", filename
#define MSG_PROMPT_FILENAME                    "Please enter filename: "
#define BACKUP_FILENAME_EXTENSION              ".bac"

// project.main.fileManager.PRIVATE_FUNCTION_DECLARATIONS
static char* _retrieveFileName(const char *msg);
static char* _addFileExtension(char *name, const char *extension);
static FILE* _openFile(const char *name, const char *mode);
static FILE* _promptDiscardLastSession (FILE* fPtr);