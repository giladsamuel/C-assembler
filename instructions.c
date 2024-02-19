#include "instructions.h"


struct {
	InstructionType instructionType;
	int operandsNumber;
	char *sourceAddressingModes;
	char *destinationAddressingModes;
} COMMANDS[] = {
		{MOV, 2, "0,1,2,3", "1,2,3"}, 
		{CMP, 2, "0,1,2,3", "0,1,2,3"},
		{ADD, 2, "0,1,2,3", "1,2,3"},
		{SUB, 2, "0,1,2,3", "1,2,3"},
		{NOT, 1, "", "1,2,3"},
		{CLR, 1, "", "1,2,3"},
		{LEA, 2, "1,2", "1,2,3"},
		{INC, 1, "", "1,2,3"},
		{DEC, 1, "", "1,2,3"},
		{JMP, 1, "", "1,3"},
		{BNE, 1, "", "1,3"},
		{RED, 1, "", "1,2,3"},
		{PRN, 1, "", "0,1,2,3"},
		{JSR, 1, "", "1,3"},
		{RTS, 0, "", ""},
		{HLT, 0, "", ""}}; 


int parseValidateInstruction(char *instructionName, char* sentence, int lineNumber) {
    InstructionType instructionType;
    int numberOfOperands;
    int sourceAddressingMode;
    int destinationAddressingMode;
    int numberOfWords;


    instructionType = identifyInstructionType(instructionName);
    if (instructionType == -1) {
        printf("\nError in line %d: Invalid instruction name - '%s'\n", lineNumber, instructionName);
        return -1;
    }
    numberOfOperands = validateInstructionCommaGetNumOfOperands(sentence, lineNumber);
    if (numberOfOperands == -1) {
        printf("Error: Invalid number of commas in instruction");
        return -1;
    }
    if (!validateNumberOfOperandsAgainstInstructionType(instructionType, numberOfOperands, lineNumber)) {
        return -1;
    }
    if (!validateInstructionOperands(instructionType, sentence, &sourceAddressingMode, &destinationAddressingMode, numberOfOperands, lineNumber)) {
        return -1;
    }
    numberOfWords = getNumberOfWordsForInstruction(sourceAddressingMode, destinationAddressingMode, numberOfOperands);
    return numberOfWords;
}


int identifyInstructionType(char *instructionName) {
    if (strcmp(instructionName, "mov") == 0) {
        return MOV;
    }
    if (strcmp(instructionName, "cmp") == 0) {
        return CMP;
    }
    if (strcmp(instructionName, "add") == 0) {
        return ADD;
    }
    if (strcmp(instructionName, "sub") == 0) {
        return SUB;
    }
    if (strcmp(instructionName, "not") == 0) {
        return NOT;
    }
    if (strcmp(instructionName, "clr") == 0) {
        return CLR;
    }
    if (strcmp(instructionName, "lea") == 0) {
        return LEA;
    }
    if (strcmp(instructionName, "inc") == 0) {
        return INC;
    }
    if (strcmp(instructionName, "dec") == 0) {
        return DEC;
    }
    if (strcmp(instructionName, "jmp") == 0) {
        return JMP;
    }
    if (strcmp(instructionName, "bne") == 0) {
        return BNE;
    }
    if (strcmp(instructionName, "red") == 0) {
        return RED;
    }
    if (strcmp(instructionName, "prn") == 0) {
        return PRN;
    }
    if (strcmp(instructionName, "jsr") == 0) {
        return JSR;
    }
    if (strcmp(instructionName, "rts") == 0) {
        return RTS;
    }
    if (strcmp(instructionName, "hlt") == 0) {
        return HLT;
    }
    return -1;
}


int validateInstructionCommaGetNumOfOperands(char *sentence, int lineNumber) {
    int numberOfOperands = 0;
    /*Empty - No Operand*/
    if (sentence == NULL) {
        return numberOfOperands; /*0*/
    }
    /* Skip leading whitespace */
    while (*sentence != '\0' && (*sentence == ' ' || *sentence == '\t')) {
        sentence++;
    }
    /*No Operand*/
    if (*sentence == '\0') {
        return numberOfOperands; /*0*/
    }
    if (*sentence == ',') {
        printf("\nError in line %d: comma before sentence - '%s'", lineNumber, sentence);
    }
    /*Skip first operand*/
    while (*sentence != '\0' && *sentence != ',' && *sentence != ' ' && *sentence != '\t') {
        sentence++;
    }
    numberOfOperands++;

    /*Skip whitespace after operand*/
    while (*sentence != '\0' && (*sentence == ' ' || *sentence == '\t')) {
        sentence++;
    }
    /*line end after operand*/
    if (*sentence == '\0') {
        return numberOfOperands; /*1*/
    }
    /*comma after operand - meaning 2 operands*/
    if (*sentence == ',') {
        sentence++;
    } else {
        printf("\nError in line %d: Missing comma", lineNumber);
        return -1;
    }
    /*Skip whitespace after comma*/
    while (*sentence != '\0' && (*sentence == ' ' || *sentence == '\t')) {
        sentence++;
    }
    if (*sentence == '\0') {
        printf("\nError in line %d: Missing argument after comma", lineNumber);
        return -1;
    }
    if (*sentence == ',') {
        printf("\nError in line %d: Multiple consecutive commas - '%s'", lineNumber, sentence);
        return -1;
    }
    /*Skip second operand*/
    while (*sentence != '\0' && *sentence != ',' && *sentence != ' ' && *sentence != '\t') {  /*asdf    dfg*/
        sentence++;
    }
    numberOfOperands++;

    /*Skip whitespace after operand*/
    while (*sentence != '\0' && (*sentence == ' ' || *sentence == '\t')) {
        sentence++;
    }
    /*line end after operand*/
    if (*sentence == '\0') {
        return numberOfOperands; /*2*/
    } else {
        printf("\nError in line %d: Extraneous text after end of command - '%s'", lineNumber, sentence);
        return -1;
    }
}


int validateNumberOfOperandsAgainstInstructionType(InstructionType instructionType, int numberOfOperands, int lineNumber) {
    if (COMMANDS[instructionType].operandsNumber != numberOfOperands) {
        printf("Error: Invalid number of operands - '%d', for instruction type %d at line %d.\n", numberOfOperands, instructionType, lineNumber);
        return 0;
    }
    return 1;
}


int validateInstructionOperands(InstructionType instructionType, char *sentence, int *sourceAddressingMode, int *destinationAddressingMode,  int numberOfOperands, int lineNumber) {
    char *firstOperand = NULL;
    char *secondOperand = NULL;

    firstOperand = strtok(sentence, " ,\t\n");
    secondOperand = strtok(NULL, " ,\t\n");

    if ( numberOfOperands == 0) {
        return 1;

    } else if (numberOfOperands == 1) {
        *destinationAddressingMode = identifyAddressingMode(firstOperand, lineNumber);
        return validateDestinationAddressingModeAgainstInstructionType(instructionType, *destinationAddressingMode, lineNumber);

    } else if (numberOfOperands == 2) {
        *sourceAddressingMode = identifyAddressingMode(firstOperand, lineNumber);
        *destinationAddressingMode = identifyAddressingMode(secondOperand, lineNumber);
        return (validateSourceAddressingModeAgainstInstructionType(instructionType, *sourceAddressingMode, lineNumber) &&
                validateDestinationAddressingModeAgainstInstructionType(instructionType, *destinationAddressingMode, lineNumber));
    }
    return -1;
}


int identifyAddressingMode(char *operand, int lineNumber) {
    if (operand == NULL) {
        return -1;
    }
    if (operand[0] == '#') {
        return 0;
    }
    if (operand[strlen(operand) - 1] == ']') {
        return 2;
    }
    if (isRegister(operand)) {
        return 3;
    }
    return 1;
}


int isRegister(char *operand) {
    if (operand[0] == 'r' && strlen(operand) == 2 && operand[1] >= '0' && operand[1] <= '7') {
        return 1;
    }
    return 0;
}

int validateDestinationAddressingModeAgainstInstructionType(InstructionType instructionType, int addressingMode, int lineNumber) {
    if (strchr(COMMANDS[instructionType].destinationAddressingModes, addressingMode + '0') == NULL) {
        printf("Error: Invalid addressing mode for operand at line %d.\n", lineNumber);
        return 0;
    }
    return 1;
}


int validateSourceAddressingModeAgainstInstructionType(InstructionType instructionType, int addressingMode, int lineNumber) {
    /*Adding '0' to an integer value result ASCII representation of that integer.*/
    if (strchr(COMMANDS[instructionType].sourceAddressingModes, addressingMode + '0') == NULL) { 
        printf("Error: Invalid addressing mode for operand at line %d.\n", lineNumber);
        return 0;
    }
    return 1;
}


int getNumberOfWordsForInstruction(int sourceAddressingMode, int destinationAddressingMode, int numberOfOperands) {
    if (numberOfOperands == 0) {
        return 1;

    } else if (numberOfOperands == 1) {
        if (sourceAddressingMode == 2) {
            return 3;
        } else {
            return 2;
        }

    } else if (numberOfOperands == 2) {
        if (sourceAddressingMode == 2 && destinationAddressingMode == 2) {
            return 5;
        } else if (sourceAddressingMode == 2 || destinationAddressingMode == 2) {
            return 4;
        } else if (sourceAddressingMode == 3 && destinationAddressingMode == 3) {
            return 2;
        } else {
            return 3;
        }
    }
    return -1;
}