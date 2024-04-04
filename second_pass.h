#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include <stdio.h>
#include "hash_table.h"
#include "first_pass.h"


int secondPass(const char* fileName, FILE *amFile, Entry *symbolHashTable[], Entry *entExtHashTable[], char *machineCodeWordsArray[]);
int parseLabelSentence(Entry *symbolHashTable[], Entry *entExtHashTable[], char *sentence, int *instructionCounter,  char *machineCodeWordsArray[], int lineNumber);

#endif