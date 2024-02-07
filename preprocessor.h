#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "hash_table.h"
#include "str_helper.h"


#define MAX_LINE_LENGTH 81 /* max line length including \n char*/

/**
 * @return Returns an integer indicating the success or failure of the conversion.
 */
int preprocessMacros(const char *fileName);

#endif