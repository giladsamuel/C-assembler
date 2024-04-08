#ifndef OUTPUT_FILES_h
#define OUTPUT_FILES_h

#include <stdio.h>

#include "hash_table.h"

int createOutputFiles(const char *fileName, FILE *amFile, int IC, int DC, char *machineCodeWordsArray[], char *dataWordsArray[], Entry *entExtHashTable[]);
void writeObjectFile(FILE *obFile, int IC, int DC, char *machineCodeWordsArray[], char *dataWordsArray[]);
void encryptWord(char encryptLine[8], char *binaryWord);
int binaryToDecimal(char *binary);
char mapToBase4(int decimal);

#endif