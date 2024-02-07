#ifndef MACRO_H
#define MACRO_H

#include <unistd.h>
#include "str_helper.h"
#include "hash_table.h"

#define MAX_LINE_LENGTH 81 /* max line length including \n char*/

/**
 * @return Returns an integer indicating the success or failure of the conversion.
 */
int macroToTable(const char *fileName);

#endif