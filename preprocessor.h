#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "hash_table.h"
#include "str_helper.h"
#include "directives.h"
#include "instructions.h"


#define MAX_LINE_LENGTH 81 /* max line length including \n char and \0*/

/**
 * Preprocess macros in a given file.
 *
 * This function reads a file line by line and performs macro substitution.
 * It searches for macro definitions and replaces macro invocations with their corresponding definitions.
 * The preprocessed output is written to a new file.
 *
 * @param fileName The name of the input file.
 * @return 1 if the preprocessing is successful, 0 otherwise.
 */
int preprocessMacros(const char *fileName);


/**
 * Checks if a macro name is valid.
 *
 * This function checks if a given macro name is valid according to the following rules:
 * - The name must not be NULL.
 * - The name must not exceed the maximum length defined by MAX_NAME_LENGTH.
 * - The name must start with a letter.
 * - The name must not be the name of an instruction or directive.
 * - The name must not be already defined in the hash table.
 *
 * @param hashTable The hash table containing the macro entries.
 * @param name The name of the macro to be checked.
 * @param lineNumber The line number where the macro is defined.
 * @return 1 if the macro name is valid, 0 otherwise.
 */
int isValidMacroName(Entry *hashTable[], const char *name, int lineNumber);

#endif