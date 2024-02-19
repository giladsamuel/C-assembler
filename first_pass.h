#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash_table.h"
#include "directives.h"
#include "instructions.h"


#define MAX_LINE_LENGTH 81

typedef enum {
    EMPTY,
    COMMENT,
    DIRECTIVE,
    INSTRUCTION,
    CONSTANT,
    LABEL
} LineType;



int firstPass(const char* fileName);
LineType identifyLineType(char *word);
int parseValidateConstant(Entry *hashTable[], char *sentence, char **constantName, int *constantValue, int lineNumber);
int parseValidateLabelSentence(Entry *symbolHashTable[], char *labelName, char *sentence, int lineNumber, int *instructionCounter, int *dataCounter);
int parseValidateInstruction(char *instructionName, char* sentence, int lineNumber);
int validateLabel(Entry *hashTable[], const char *label, int lineNumber);
void updateDataSymbols(Entry *symbolHashTable[], int instructionOffset);

#endif