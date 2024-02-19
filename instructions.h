#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MEMORY_OFFSET 100

enum {
    NO_OPERAND,
    ALL,
    NO_NUMBER,
    LABEL_INDEX,
    LABEL_REGISTER
} ;

typedef enum {
    MOV,
    CMP,
    ADD,
    SUB,
    NOT,
    CLR,
    LEA,
    INC,
    DEC,
    JMP,
    BNE,
    RED,
    PRN,
    JSR,
    RTS,
    HLT
} InstructionType;

int identifyInstructionType(char *instructionName);
int validateInstructionCommaGetNumOfOperands(char *sentence, int lineNumber);
int validateNumberOfOperandsAgainstInstructionType(InstructionType instructionType, int numberOfOperands, int lineNumber);
int validateInstructionOperands(InstructionType instructionType, char *sentence, int *sourceAddressingMode, int *destinationAddressingMode,  int numberOfOperands, int lineNumber);
int identifyAddressingMode(char *operand, int lineNumber);
int isRegister(char *operand);
int validateDestinationAddressingModeAgainstInstructionType(InstructionType instructionType, int addressingMode, int lineNumber);
int validateSourceAddressingModeAgainstInstructionType(InstructionType instructionType, int addressingMode, int lineNumber);
int getNumberOfWordsForInstruction(int sourceAddressingMode, int destinationAddressingMode, int numberOfOperands);

#endif