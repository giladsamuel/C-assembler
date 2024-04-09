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
#define MAX_INSTRUCTIONS 100

#define NOT !

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
int parseValidateConstant(Entry *symbolHashTable[], Entry *entExtHashTable[], char *sentence, char **constantName, int *constantValue, int lineNumber);
int parseValidateLabelSentence(Entry *symbolHashTable[], Entry *entExtHashTable[], char *labelName, char *sentence, int lineNumber, int *instructionCounter, int *dataCounter, char *dataWordsArray[]);
int validateLabel(Entry *symbolHashTable[], Entry *entExtHashTable[], const char *label, int lineNumber);
int isValidName(struct Entry *hashTable[], const char *name, int lineNumber);
int isValidValue(const char *value);
void updateDataSymbols(Entry *symbolHashTable[], int instructionOffset);
void updateEntranceValue(Entry *symbolHashTable[], Entry *entExtHashTable[]);

#endif