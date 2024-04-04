#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "binary_word.h"
#include "instruction_type.h"
#include "hash_table.h"

#define MEMORY_OFFSET 100


enum {
    NO_OPERAND,
    ALL,
    NO_NUMBER,
    LABEL_INDEX,
    LABEL_REGISTER
} ;

enum {
    IMMEDIATE,
    DIRECT,
    INDEX_ARRAY,
    REGISTER
};

int parseValidateInstruction(char *instructionName, char* sentence, int lineNumber);
int identifyInstructionType(char *instructionName);
int validateInstructionCommaGetNumOfOperands(char *sentence, int lineNumber);
int validateNumberOfOperandsAgainstInstructionType(InstructionType instructionType, int numberOfOperands, int lineNumber);
int validateInstructionOperands(InstructionType instructionType, char *sentence, int *sourceAddressingMode, int *destinationAddressingMode,  int numberOfOperands, int lineNumber);
int identifyAddressingMode(char *operand, int lineNumber);
int isRegister(char *operand);
int validateDestinationAddressingModeAgainstInstructionType(InstructionType instructionType, int addressingMode, int lineNumber);
int validateSourceAddressingModeAgainstInstructionType(InstructionType instructionType, int addressingMode, int lineNumber);
int getNumberOfWordsForInstruction(int sourceAddressingMode, int destinationAddressingMode, int numberOfOperands);
int parseInstructionToBinary(Entry *symbolHashTable[], Entry *entExtHashTable[], char *instructionName, char *sentence, int instructionCounter, char *machineCodeWordsArray[]);
int getInstructionOperands(char **firstOperandP, char **secondOperandP, char *sentence, int *sourceAddressingMode, int *destinationAddressingMode,  int numberOfOperands);
int getInstructionBinaryWords(Entry *symbolHashTable[], Entry *entExtHashTable[], int numberOfOperands, char *firstOperand, char *secondOperand, int sourceAddressingMode, int destinationAddressingMode, int instructionCounter, char *machineCodeWordsArray[]);

int immediateToBinary(Entry *symbolHashTable[], char *operand, int instructionCounter, char *machineCodeWordsArray[]);
int directToBinary(Entry *symbolHashTable[], Entry *entExtHashTable[], char *operandLabel, int instructionCounter, char *machineCodeWordsArray[]);
int indexArrayToBinary(Entry *symbolHashTable[], Entry *entExtHashTable[], char *operand, int instructionCounter, char *machineCodeWordsArray[]);
int registerToBinary(char *sourceOperand, char *destinationOperand, int instructionCounter, char *machineCodeWordsArray[]);
#endif