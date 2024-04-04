#ifndef BINARY_WORD_H
#define BINARY_WORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instruction_type.h"

#define WORD_SIZE 14
#define MAX_VALUE 8191
#define MIN_VALUE -8192

void valueToDataBinaryWord(int value, char binaryWord[WORD_SIZE + 1]);
void valueToCodeBinaryWord(int value, char binaryWord[WORD_SIZE + 1]);
int instructionFirstBinaryWord(InstructionType instructionType, int sourceAddressingMode, int destinationAddressingMode, char *machineCodeWord, char *opcode);
char *addressingModeToBinary(int addressingMode);
int registerBinaryWord(int sourceRegNum, int destinationRegNum, char *codeWord);

void printBinaryWordsArray(char *dataWordsArray[], int dataCounter);
void freeBinaryWordsArray(char *dataWordsArray[], int dataCounter);

#endif