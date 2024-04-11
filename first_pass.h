#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash_table.h"
#include "directives.h"
#include "instructions.h"
#include "second_pass.h"
#include "binary_word.h"
#include "output_files.h"

#define MAX_LINE_LENGTH 81
#define MAX_INSTRUCTIONS 1000

#define NOT !

typedef enum {
    EMPTY,
    COMMENT,
    DIRECTIVE,
    INSTRUCTION,
    CONSTANT,
    LABEL
} LineType;


/**
 * Performs compiler's first pass of the assembly file.
 * If no errors occurred during the first pass, the function calls the second pass.
 * If no errors occurred during the second pass, the function creates the output files.
 * 
 * @param fileName The name of the assembly file.
 * @return Returns 0 if no errors occurred during the compiler work, otherwise returns 1.
 */
int firstPass(const char* fileName);


/**
 * Identifies the type of a line based on the given first word.
 *
 * @param word The word to be identified.
 * @return The type of the line.
 */
LineType identifyLineType(char *word);


/**
 * Parses and validates a constant definition in the assembly code.
 *
 * @param symbolHashTable The symbol hash table.
 * @param entExtHashTable The entry/extern hash table.
 * @param sentence The assembly code sentence containing the constant definition.
 * @param constantName Pointer to store the name of the constant.
 * @param constantValue Pointer to store the value of the constant.
 * @param lineNumber The line number of the constant definition.
 * @return 1 if the constant is parsed and validated successfully, 0 otherwise.
 */
int parseValidateConstant(Entry *symbolHashTable[], Entry *entExtHashTable[], char *sentence, char **constantName, int *constantValue, int lineNumber);


/**
 * Parses and validates a label sentence.
 *
 * This function takes in a symbol hash table, an external entry hash table, a label name, a sentence, a line number,
 * instruction counter, data counter, and a data words array. It parses and validates the given sentence, checking for
 * various error conditions such as empty lines, comments, constants after a label, labels after a label, and more.
 * It also identifies the type of the first word in the sentence (empty, comment, constant, label, directive, or instruction)
 * and performs appropriate actions based on the type.
 *
 * @param symbolHashTable The symbol hash table.
 * @param entExtHashTable The external entry hash table.
 * @param labelName The label name.
 * @param sentence The sentence to parse and validate.
 * @param lineNumber The line number.
 * @param instructionCounter The instruction counter.
 * @param dataCounter The data counter.
 * @param dataWordsArray The data words array.
 * @return The number of values or words parsed and validated, or -1 if an error occurred.
 */
int parseValidateLabelSentence(Entry *symbolHashTable[], Entry *entExtHashTable[], char *labelName, char *sentence, int lineNumber, int *instructionCounter, int *dataCounter, char *dataWordsArray[]);


/**
 * Validates a label by checking if it has a valid name and if it is already defined as external.
 * 
 * @param symbolHashTable The symbol hash table.
 * @param entExtHashTable The entry/external hash table.
 * @param label The label to validate.
 * @param lineNumber The line number where the label is found.
 * @return 1 if the label is valid, 0 otherwise.
 */
int validateLabel(Entry *symbolHashTable[], Entry *entExtHashTable[], const char *label, int lineNumber);


/**
 * @brief Checks if a given name is valid.
 * 
 * This function checks if a given name meets the following criteria:
 * - The name is not NULL.
 * - The name is not longer than MAX_NAME_LENGTH characters.
 * - The name starts with a letter.
 * - The name contains only letters and digits.
 * - The name is not a reserved instruction or directive name.
 * - The name is not already defined in the hash table.
 * 
 * @param hashTable The hash table containing the defined names.
 * @param name The name to be checked.
 * @param lineNumber The line number where the name is encountered.
 * @return 1 if the name is valid, 0 otherwise.
 */
int isValidName(struct Entry *hashTable[], const char *name, int lineNumber);


/**
 * @brief Checks if a given value is a valid integer.
 * 
 * This function takes a string value as input and checks if it is a valid integer.
 * A valid integer can be positive or negative and must contain only digits.
 * 
 * @param value The string value to be checked.
 * @return 1 if the value is a valid integer, 0 otherwise.
 */
int isValidValue(const char *value);


/**
 * Updates the values of data symbols in the symbol hash table by adding the instruction offset.
 * 
 * @param symbolHashTable The symbol hash table.
 * @param instructionOffset The instruction offset to be added to the values of data symbols.
 */
void updateDataSymbols(Entry *symbolHashTable[], int instructionOffset);


/**
 * Updates the value of entrance properties in the entExtHashTable
 * based on the corresponding value in the symbolHashTable.
 *
 * @param symbolHashTable The symbol hash table containing the symbol entries.
 * @param entExtHashTable The entExt hash table containing the entrance and external entries.
 */
void updateEntranceValue(Entry *symbolHashTable[], Entry *entExtHashTable[]);

#endif