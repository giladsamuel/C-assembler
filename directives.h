#ifndef DIRECTIVES_H
#define DIRECTIVES_H

#include "hash_table.h"
#include "first_pass.h"
#include "binary_word.h"

typedef enum Directive{
    DATA,
    STRING,
    ENTRY,
    EXTERN
} DirectiveType;



/**
 * Identifies the type of directive based on the given directive string.
 *
 * @param directive The directive string to be identified.
 * @return The DirectiveType enum value representing the type of directive.
 *         Returns -1 if the directive is not recognized.
 */
DirectiveType identifyDirectiveType(const char *directive);


/**
 * Parses and validates a directive based on its type.
 *
 * @param symbolHashTable The symbol hash table.
 * @param entExtHashTable The entry/extern hash table.
 * @param sentence The directive sentence.
 * @param directiveType The type of the directive.
 * @param lineNumber The line number of the directive.
 * @param dataCounter The data counter.
 * @param dataWordsArray The array of data words.
 * @return The number of values parsed and validated, or -1 if the directive is invalid.
 */
int parseValidateDirective(Entry *symbolHashTable[], Entry *entExtHashTable[], char *sentence, DirectiveType directiveType, int lineNumber, int dataCounter, char *dataWordsArray[]);


/**
 * Parses and validates the data directive in the assembly code.
 * 
 * @param symbolHashTable The symbol hash table.
 * @param sentence The sentence containing the data directive.
 * @param lineNumber The line number of the data directive.
 * @param dataCounter The current data counter.
 * @param dataWordsArray The array to store the data words.
 * @return The number of values parsed and validated, or -1 if an error occurred.
 */
int parseValidateDataDirective(Entry *symbolHashTable[], char *sentence, int lineNumber, int dataCounter, char *dataWordsArray[]);


/**
 * Parses and validates a string directive.
 *
 * This function takes a sentence, line number, data counter, and an array of data words as input.
 * It checks if the sentence is NULL and returns an error if it is.
 * It then checks if the sentence starts and ends with double quotes and returns an error if it doesn't.
 * Next, it calculates the number of characters in the string without the quotes and allocates memory for each character.
 * It checks if each character is representable by 14 bits and returns an error if it isn't.
 * Finally, it assigns the binary representation of each character to the data words array.
 *
 * @param sentence The sentence to parse and validate.
 * @param lineNumber The line number of the sentence.
 * @param dataCounter The current data counter.
 * @param dataWordsArray The array of data words.
 * @return The number of characters in the string if it is valid, or -1 if there is an error.
 */
int parseValidateStringDirective(char *sentence, int lineNumber, int dataCounter, char *dataWordsArray[]);


/**
 * Parses, validates, and inserts an entry or extern directive into symbol and entry/extern hash tables.
 *
 * @param symbolHashTable The symbol hash table.
 * @param entExtHashTable The entry/extern hash table.
 * @param sentence The input sentence to parse.
 * @param lineNumber The line number of the input sentence.
 * @param myProperty The property of the directive (entry or extern).
 * @return Returns 0 if successful, -1 if an error occurs.
 */
int parseValidateInsertEntryExternDirective(Entry *symbolHashTable[], Entry *entExtHashTable[], char *sentence, int lineNumber, Property property);

#endif