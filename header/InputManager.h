/*
 * InputManager.h
 * InputManager.h contains necesary information to
 * parse information from input file or user input.
 *
 * Developer:           Gon Kim (imgonkim@gmail.com)
 * Initial Commit:      03182013_004815
 * Last Major Update:   03182013_004815
 *
 */

#include <stdio.h>
char* retrieveFileName(const char *msg);
char* readOneLine(FILE* fPtr);
void* readSingleField(input_type type, char **line);