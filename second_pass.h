#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include <stdio.h>
#include "hash_table.h"
#include "first_pass.h"

/**
 * @brief Performs the second pass of the compiler process.
 *
 * This function reads the assembly file line by line and processes each line according to its type and make machine code words.
 * It identifies the line type (empty, comment, constant, label, directive, or instruction) and performs the necessary actions.
 * For label lines, it calls the parseLabelSentence function to handle the label definition.
 * For instruction lines, it calls the parseInstructionToBinary function to convert the instruction to binary code.
 *
 * @param fileName The name of the assembly file.
 * @param amFile The pointer to the opened assembly file.
 * @param symbolHashTable The symbol hash table containing label definitions.
 * @param entExtHashTable The entry/external hash table containing entry and external labels.
 * @param machineCodeWordsArray The array to store the machine code words.
 * @return Returns 0 if the second pass is successful, otherwise returns a non-zero value indicating an error.
 */
int secondPass(const char* fileName, FILE *amFile, Entry *symbolHashTable[], Entry *entExtHashTable[], char *machineCodeWordsArray[]);


/**
 * Parses a label sentence and updates the symbol hash table, entry/external hash table, instruction counter, and machine code words array.
 * Make binary code for the instruction and store it in the machine code words array.
 * 
 * @param symbolHashTable The symbol hash table.
 * @param entExtHashTable The entry/external hash table.
 * @param sentence The sentence to parse.
 * @param instructionCounter The current instruction counter.
 * @param machineCodeWordsArray The machine code words array.
 * @param lineNumber The current line number.
 * @return The number of words parsed, or 0 if the first word is empty, a comment, a constant, a label, or a directive.
 *         If the first word is an instruction, it returns the number of words parsed.
 *         If an invalid instruction is encountered, it returns -1.
 */
int parseLabelSentence(Entry *symbolHashTable[], Entry *entExtHashTable[], char *sentence, int *instructionCounter,  char *machineCodeWordsArray[], int lineNumber);

#endif