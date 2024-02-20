#ifndef STR_HELPER_H
#define STR_HELPER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/**
 * Creates a new string by joining two input strings.
 * If memory allocation fails, the function prints an error message and returns NULL.
 * 
 * @param str1 The first string to be joined.
 * @param str2 The second string to be joined.
 * @return The newly created string that is a concatenation of str1 and str2.  
 */
char *crateJoinString(const char *str1, const char *str2);

/**
 * Creates a duplicate of the input string.
 * return The newly created string that is a duplicate of the input string.
 * If memory allocation fails, the function prints an error message and returns NULL.
 * @param str The string to be duplicated.
 * @return The newly created string that is a duplicate of the input string. 
 */
char *strdup(const char *str);


#endif