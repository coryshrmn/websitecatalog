/*
 * SingleWebsiteManager.h
 * SingleWebsiteManager parses information from the file pointer
 * and returns Website struct
 *
 * Developer:           Gon Kim (imgonkim@gmail.com)
 * Initial Commit:      03162013_215826
 * Last Major Update:   03162013_215826
 */

// project.main.SingleWebsiteManager.CONSTANT_DEFINED
#define MSG_PROMPT_EXIT_ON_INVALID_FIELD        "Invalid field has been read. Enter your selection\n"

// project.main.SingleWebsiteManager.PRIVATE_FUNCTION_DECLARATIONS
static char* _readOneLine(FILE* fPtr);
static void* _readSingleField(input_type type, char **line);