#ifndef BINARY_WORD_H
#define BINARY_WORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instruction_type.h"

#define WORD_SIZE 14

#define FOURTEEN_BIT_MIN -8192
#define FOURTEEN_BIT_MAX 8191

#define TWELVE_BIT_MIN -2048
#define TWELVE_BIT_MAX 2047

void valueToDataBinaryWord(int value, char binaryWord[WORD_SIZE + 1]);
void valueToCodeBinaryWord(int value, char binaryWord[WORD_SIZE + 1]);
int isRepresentableBy12Bits(int value);
int isRepresentableBy14Bits(int value);
int instructionFirstBinaryWord(InstructionType instructionType, int sourceAddressingMode, int destinationAddressingMode, char *machineCodeWord, char *opcode);
char *addressingModeToBinary(int addressingMode);
int registerBinaryWord(int sourceRegNum, int destinationRegNum, char *codeWord);
void printBinaryWordsArray(char *dataWordsArray[], int dataCounter);
void freeBinaryWordsArray(char *dataWordsArray[], int dataCounter);
int binaryToDecimal(char *binary);

#endif