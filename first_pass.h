#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash_table.h"
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


typedef enum Directive{
    DATA,
    STRING,
    ENTRY,
    EXTERN
} DirectiveType;


int firstPass(const char* fileName);
LineType identifyLineType(char *word);
DirectiveType identifyDirectiveType(char *directive);
int parseValidateConstant(Entry *hashTable[], char *sentence, char **constantName, int *constantValue, int lineNumber);
int parseValidateLabelSentence(Entry *symbolHashTable[], char *labelName, char *sentence, int lineNumber, int *instructionCounter, int *dataCounter);
int parseValidateDirective(Entry *symbolHashTable[], char *sentence, DirectiveType directiveType, int lineNumber);
int parseValidateDataDirective(Entry *symbolHashTable[], char *sentence, int lineNumber);
int parseValidateStringDirective(char *sentence, int lineNumber);
int parseValidateInsertEntryExternDirective(Entry *symbolHashTable[], char *sentence, int lineNumber, Property property);
int parseValidateInstruction(char *instructionName, char* sentence, int lineNumber);
int isValidName(Entry * hashTable[], const char *name);
int isValidValue(const char *value);
Entry *insertSymbolEntry(Entry *ht[TABLE_SIZE], const char *name, int property, int value);
int validateLabel(Entry *hashTable[], const char *label, int lineNumber);
void updateDataSymbols(Entry *symbolHashTable[], int instructionOffset);

#endif