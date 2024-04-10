#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "hash_table.h"
#include "str_helper.h"
#include "directives.h"
#include "instructions.h"


#define MAX_LINE_LENGTH 81 /* max line length including \n char and \0*/

/**
 * @return Returns an integer indicating the success or failure of the conversion.
 */
int preprocessMacros(const char *fileName);
int isValidMacroName(Entry *hashTable[], const char *name, int lineNumber);

#endif