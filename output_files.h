#ifndef OUTPUT_FILES_h
#define OUTPUT_FILES_h

#include <stdio.h>

#include "hash_table.h"

int createOutputFiles(const char *fileName, int IC, int DC, char *machineCodeWordsArray[], char *dataWordsArray[], Entry *entExtHashTable[]);
FILE *creatOpenFile(const char *fileName, char *fileExtention);
void writeObjectFile(FILE *obFile, int IC, int DC, char *machineCodeWordsArray[], char *dataWordsArray[]);
void writeEntExtFile(FILE *entFile, Entry *entExtHashTable[], Property propertyType);
void encryptWord(char encryptLine[8], char *binaryWord);
int binaryToDecimal(char *binary);
char mapToBase4(int decimal);
int isThereEntExt(Entry *entExtHashTable[], Property propertyType);

#endif