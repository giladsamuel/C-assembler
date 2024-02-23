#ifndef BINARY_WORD_H
#define BINARY_WORD_H

#include <stdio.h>
#include <stdlib.h>

#define WORD_SIZE 14
#define MAX_VALUE 8191
#define MIN_VALUE -8192

void dataToBinaryWord(int data, char binaryWord[WORD_SIZE + 1]);

void printBinaryWordsArray(char *dataWordsArray[], int dataCounter);
void freeBinaryWordsArray(char *dataWordsArray[], int dataCounter);

#endif