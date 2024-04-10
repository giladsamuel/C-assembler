#include "instructions.h"


struct {
	InstructionType instructionType;
	int operandsNumber;
	char *sourceAddressingModes;
	char *destinationAddressingModes;
    char *opcode;
} COMMANDS[] = {
        {MOV, 2, "0,1,2,3", "1,2,3", "0000"}, 
        {CMP, 2, "0,1,2,3", "0,1,2,3", "0001"},
        {ADD, 2, "0,1,2,3", "1,2,3", "0010"},
        {SUB, 2, "0,1,2,3", "1,2,3", "0011"},
        {NOT, 1, "", "1,2,3", "0100"},
        {CLR, 1, "", "1,2,3", "0101"},
        {LEA, 2, "1,2", "1,2,3", "0110"},
        {INC, 1, "", "1,2,3", "0111"},
        {DEC, 1, "", "1,2,3", "1000"},
        {JMP, 1, "", "1,3", "1001"},
        {BNE, 1, "", "1,3", "1010"},
        {RED, 1, "", "1,2,3", "1011"},
        {PRN, 1, "", "0,1,2,3", "1100"},
        {JSR, 1, "", "1,3", "1101"},
        {RTS, 0, "", "", "1110"},
        {HLT, 0, "", "", "1111"}}; 


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
        printf("Error: Invalid number of commas in instruction\n");
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


int identifyInstructionType(const char *instructionName) {
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
        printf("\nError in line %d: comma before sentence - '%s'\n", lineNumber, sentence);
        return -1;
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
        printf("\nError in line %d: Missing comma\n", lineNumber);
        return -1;
    }
    /*Skip whitespace after comma*/
    while (*sentence != '\0' && (*sentence == ' ' || *sentence == '\t')) {
        sentence++;
    }
    if (*sentence == '\0') {
        printf("\nError in line %d: Missing argument after comma\n", lineNumber);
        return -1;
    }
    if (*sentence == ',') {
        printf("\nError in line %d: Multiple consecutive commas - '%s'\n", lineNumber, sentence);
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
        printf("\nError in line %d: Extraneous text after end of command - '%s'\n", lineNumber, sentence);
        return -1;
    }
}


int validateNumberOfOperandsAgainstInstructionType(InstructionType instructionType, int numberOfOperands, int lineNumber) {
    if (COMMANDS[instructionType].operandsNumber != numberOfOperands) {
        printf("\nError in line %d: Invalid number of operands - '%d', for instruction type %d.\n", lineNumber, numberOfOperands, instructionType);
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
        return IMMEDIATE;
    }
    if (isIndexArray(operand)) {
        return INDEX_ARRAY;
    }
    if (isRegister(operand) != -1) {
        return REGISTER;
    }
    return DIRECT;
}


int isRegister(char *operand) {
    if (operand != NULL && operand[0] == 'r' && strlen(operand) == 2 && operand[1] >= '0' && operand[1] <= '7') {
        return operand[1] - '0';
    }
    return -1;
}


int isIndexArray(char *operand) {
    if(operand[strlen(operand) - 1] == ']' && strchr(operand, '[') != NULL && strchr(strchr(operand, '['), ' ') == NULL) {
        return 1;
    }
    return 0;
}


int validateDestinationAddressingModeAgainstInstructionType(InstructionType instructionType, int addressingMode, int lineNumber) {
    if (strchr(COMMANDS[instructionType].destinationAddressingModes, addressingMode + '0') == NULL) {
        printf("\nError in line %d: Invalid destination addressing mode for operand.\n", lineNumber);
        return 0;
    }
    return 1;
}


int validateSourceAddressingModeAgainstInstructionType(InstructionType instructionType, int addressingMode, int lineNumber) {
    /*Adding '0' to an integer value result ASCII representation of that integer.*/
    if (strchr(COMMANDS[instructionType].sourceAddressingModes, addressingMode + '0') == NULL) { 
        printf("\nError in line %d: Invalid source addressing mode for operand.\n", lineNumber);
        return 0;
    }
    return 1;
}


int getNumberOfWordsForInstruction(int sourceAddressingMode, int destinationAddressingMode, int numberOfOperands) {
    if (numberOfOperands == 0) {
        return 1;

    } else if (numberOfOperands == 1) {
        if (destinationAddressingMode == INDEX_ARRAY) {
            return 3;
        } else {
            return 2;
        }

    } else if (numberOfOperands == 2) {
        if (sourceAddressingMode == INDEX_ARRAY && destinationAddressingMode == INDEX_ARRAY) {
            return 5;
        } else if (sourceAddressingMode == INDEX_ARRAY || destinationAddressingMode == INDEX_ARRAY) {
            return 4;
        } else if (sourceAddressingMode == REGISTER && destinationAddressingMode == REGISTER) {
            return 2;
        } else {
            return 3;
        }
    }
    return -1;
}


int parseInstructionToBinary(Entry *symbolHashTable[], Entry *entExtHashTable[], char *instructionName, char *sentence, int instructionCounter, char *machineCodeWordsArray[], int lineNumber) {
    InstructionType instructionType;
    char *firstOperand = NULL;
    char *secondOperand = NULL;
    int numberOfOperands;
    int sourceAddressingMode = 0;  /*Set by default to 0 in case there is only one or no operands (destination)*/
    int destinationAddressingMode = 0;  /* If there is only one operand, its defined as destination*/
    int numberOfWords;
    char *opcode = NULL;
    char *codeWord = NULL;


    instructionType = identifyInstructionType(instructionName);

    numberOfOperands = validateInstructionCommaGetNumOfOperands(sentence, -1);

    getInstructionOperands(&firstOperand, &secondOperand, sentence, &sourceAddressingMode, &destinationAddressingMode, numberOfOperands);

    codeWord = (char *)malloc(sizeof(char) * WORD_SIZE + 1);
    if (codeWord == NULL) {
        printf("\nError: Memory allocation failed\n");
        return -1;
    }
    opcode = COMMANDS[instructionType].opcode;
    if(!instructionFirstBinaryWord(instructionType, sourceAddressingMode, destinationAddressingMode, codeWord, opcode)) {
        printf("Error: Can't allocate memory for code word");
        return -1;
    }
    machineCodeWordsArray[instructionCounter] = codeWord;

    numberOfWords = getInstructionBinaryWords(symbolHashTable, entExtHashTable, numberOfOperands, firstOperand, secondOperand, sourceAddressingMode, destinationAddressingMode, instructionCounter, machineCodeWordsArray, lineNumber);



    return numberOfWords;
}


int getInstructionOperands(char **firstOperandP, char **secondOperandP, char *sentence, int *sourceAddressingMode, int *destinationAddressingMode,  int numberOfOperands) {

    *firstOperandP = strtok(sentence, " ,\t\n");
    *secondOperandP = strtok(NULL, " ,\t\n");

    if (numberOfOperands == 0) {
        return 1;

    } else if (numberOfOperands == 1) {
        *destinationAddressingMode = identifyAddressingMode(*firstOperandP, -1);
        return 1;

    } else if (numberOfOperands == 2) {
        *sourceAddressingMode = identifyAddressingMode(*firstOperandP, -1);
        *destinationAddressingMode = identifyAddressingMode(*secondOperandP, -1);
        return 1;
    }
    return -1;
}


int getInstructionBinaryWords(Entry *symbolHashTable[], Entry *entExtHashTable[], int numberOfOperands, char *firstOperand, char *secondOperand, int sourceAddressingMode, int destinationAddressingMode, int instructionCounter, char *machineCodeWordsArray[], int lineNumber) {
    int firstErrFlag = 0;
    int secondErrFlag = 0;
    if (numberOfOperands == 0) {
        return 1;

    } else if (numberOfOperands == 1) {
            if (destinationAddressingMode == IMMEDIATE) {
                firstErrFlag = immediateToBinary(symbolHashTable, firstOperand, instructionCounter, machineCodeWordsArray, lineNumber);
            } else if (destinationAddressingMode == DIRECT) {
                firstErrFlag = directToBinary(symbolHashTable, entExtHashTable, firstOperand, instructionCounter, machineCodeWordsArray, lineNumber);
            } else if (destinationAddressingMode == INDEX_ARRAY) {
                firstErrFlag = indexArrayToBinary(symbolHashTable, entExtHashTable, firstOperand, instructionCounter, machineCodeWordsArray, lineNumber);
            } else if (destinationAddressingMode == REGISTER) {
                firstErrFlag = registerToBinary(NULL, firstOperand, instructionCounter, machineCodeWordsArray);
            }
            if (firstErrFlag) {
                return -1;
            }
            return destinationAddressingMode == INDEX_ARRAY ? 3 : 2;                    
        
    } else if (numberOfOperands == 2) {
        if (sourceAddressingMode == INDEX_ARRAY && destinationAddressingMode == INDEX_ARRAY) {
            firstErrFlag = indexArrayToBinary(symbolHashTable, entExtHashTable, firstOperand, instructionCounter, machineCodeWordsArray, lineNumber);
            secondErrFlag = indexArrayToBinary(symbolHashTable, entExtHashTable, secondOperand, instructionCounter + 2, machineCodeWordsArray, lineNumber);
            if (firstErrFlag || secondErrFlag){
                return -1;
            }
            return 5;
        } else if (sourceAddressingMode == REGISTER && destinationAddressingMode == REGISTER) {
            firstErrFlag = registerToBinary(firstOperand, secondOperand, instructionCounter, machineCodeWordsArray);
            if (firstErrFlag) {
                return -1;
            }
            return 2;
        } else if (sourceAddressingMode == INDEX_ARRAY) {
                firstErrFlag = indexArrayToBinary(symbolHashTable, entExtHashTable, firstOperand, instructionCounter, machineCodeWordsArray, lineNumber);

                if (destinationAddressingMode == IMMEDIATE) {
                    secondErrFlag = immediateToBinary(symbolHashTable, secondOperand, instructionCounter + 2, machineCodeWordsArray, lineNumber);
                } else if (destinationAddressingMode == DIRECT) {
                    secondErrFlag = directToBinary(symbolHashTable, entExtHashTable, secondOperand, instructionCounter + 2, machineCodeWordsArray, lineNumber);
                } else if (destinationAddressingMode == REGISTER) {
                    secondErrFlag = registerToBinary(firstOperand, secondOperand, instructionCounter + 2, machineCodeWordsArray);
                }

        } else if (destinationAddressingMode == INDEX_ARRAY) {
            if (sourceAddressingMode == IMMEDIATE) {
                firstErrFlag = immediateToBinary(symbolHashTable, firstOperand, instructionCounter, machineCodeWordsArray, lineNumber);
            } else if (sourceAddressingMode == DIRECT) {
                firstErrFlag = directToBinary(symbolHashTable, entExtHashTable, firstOperand, instructionCounter, machineCodeWordsArray, lineNumber);
            } else if (sourceAddressingMode == REGISTER) {
                firstErrFlag = registerToBinary(firstOperand, secondOperand, instructionCounter, machineCodeWordsArray);
            }
            secondErrFlag = indexArrayToBinary(symbolHashTable, entExtHashTable, secondOperand, instructionCounter + 1, machineCodeWordsArray, lineNumber);
        
        } else {
            if (sourceAddressingMode == IMMEDIATE) {
                firstErrFlag = immediateToBinary(symbolHashTable, firstOperand, instructionCounter, machineCodeWordsArray, lineNumber);
            } else if (sourceAddressingMode == DIRECT) {
                firstErrFlag = directToBinary(symbolHashTable, entExtHashTable, firstOperand, instructionCounter, machineCodeWordsArray, lineNumber);
            } else if (sourceAddressingMode == REGISTER) {
                firstErrFlag = registerToBinary(firstOperand, secondOperand, instructionCounter, machineCodeWordsArray);
            }
            if (destinationAddressingMode == IMMEDIATE) {
                secondErrFlag = immediateToBinary(symbolHashTable, secondOperand, instructionCounter + 1, machineCodeWordsArray, lineNumber);
            } else if (destinationAddressingMode == DIRECT) {
                secondErrFlag = directToBinary(symbolHashTable, entExtHashTable, secondOperand, instructionCounter + 1, machineCodeWordsArray, lineNumber);
            } else if (destinationAddressingMode == REGISTER) {
                secondErrFlag = registerToBinary(firstOperand, secondOperand, instructionCounter + 1, machineCodeWordsArray);
            }
        }
        if (firstErrFlag || secondErrFlag){
            return -1;
        }
        return sourceAddressingMode == INDEX_ARRAY || destinationAddressingMode == INDEX_ARRAY ? 4 : 3;
    }
    return -1;
}


int immediateToBinary(Entry *symbolHashTable[], char *operand, int instructionCounter, char *machineCodeWordsArray[], int lineNumber) {
    char *valueStr = NULL;
    char *codeWord = NULL;
    char *endptr = NULL;
    int val;
    Entry *symbol = NULL;

    codeWord = (char *)malloc(sizeof(char) * WORD_SIZE + 1);
    if (codeWord == NULL) {
        printf("\nError: Memory allocation failed\n");
        return 1;
    }

    valueStr = strtok(operand, "#");
    val = (int)strtol(valueStr, &endptr, 10);
    if (endptr == valueStr) {
        symbol = getEntry(symbolHashTable, valueStr);
        if (symbol == NULL) {
            printf("\nError in line %d: undefined immediate name - %s\n", lineNumber ,valueStr);
            free(codeWord);
            return 1;
        }
        val = symbol->value;
    }
    if (!isRepresentableBy12Bits(val)) {
        printf("\nError in line %d: Immediate value is out of range - %d\n", lineNumber, val);
        free(codeWord);
        return 1;
    }
    valueToCodeBinaryWord(val, codeWord);
    strcat(codeWord, ABSOLUTE_ADD);
    machineCodeWordsArray[instructionCounter + 1] = codeWord;

    return 0;
}


int directToBinary(Entry *symbolHashTable[], Entry *entExtHashTable[], char *operandLabel, int instructionCounter, char *machineCodeWordsArray[], int lineNumber) {
    char *codeWord = NULL;
    Entry *labelSymbolEntry = NULL;
    Entry *labelEntExtEntry = NULL;
    int labelAddress;
    Entry *entry = NULL;


    codeWord = (char *)malloc(sizeof(char) * WORD_SIZE + 1);
    if (codeWord == NULL) {
        printf("\nError: Memory allocation failed\n");
        return 1;
    }
    labelSymbolEntry = getEntry(symbolHashTable, operandLabel);
    labelEntExtEntry = getEntry(entExtHashTable, operandLabel);
    if (labelSymbolEntry != NULL) {
        labelAddress = labelSymbolEntry->value;
        valueToCodeBinaryWord(labelAddress, codeWord);
        strcat(codeWord, RELOCATABLE_ADD);

    } else if (labelEntExtEntry != NULL && labelEntExtEntry->property == EXTERNAL) {
        entry = insertSymbolEntExtEntry(entExtHashTable, operandLabel, EXTERNAL, instructionCounter + 1 + MEMORY_OFFSET);
        if (entry == NULL) {
        return 1;
        }
        valueToCodeBinaryWord(0, codeWord);
        strcat(codeWord, EXTERNAL_ADD);
    } else {
        printf("\nError in line %d: undefined direct name - %s\n", lineNumber ,operandLabel);
        free(codeWord);
        return 1;
    }
    
    machineCodeWordsArray[instructionCounter + 1] = codeWord;

    return 0;
}


int indexArrayToBinary(Entry *symbolHashTable[], Entry *entExtHashTable[], char *operand, int instructionCounter, char *machineCodeWordsArray[], int lineNumber) {
    char *codeWord = NULL;
    char *arrayName = NULL;
    char *indexStr = NULL;
    Entry *arraySymbolEntry = NULL;
    Entry *arrayEntExtEntry = NULL;
    int arrayAddress;
    int index;
    char *endptr = NULL;
    Entry *symbol = NULL;
    Entry *entry = NULL;


    arrayName = strtok(operand, "[");
    indexStr = strtok(NULL, "]");

    /*array*/
    codeWord = (char *)malloc(sizeof(char) * WORD_SIZE + 1);
    if (codeWord == NULL) {
        printf("\nError: Memory allocation failed\n");
        return 1;
    }
    arraySymbolEntry = getEntry(symbolHashTable, arrayName);
    arrayEntExtEntry = getEntry(entExtHashTable, arrayName);
    if (arraySymbolEntry != NULL) {
        arrayAddress = arraySymbolEntry->value;
        valueToCodeBinaryWord(arrayAddress, codeWord);
        strcat(codeWord, RELOCATABLE_ADD);

    } else if (arrayEntExtEntry != NULL && arrayEntExtEntry->property == EXTERNAL) {
        entry = insertSymbolEntExtEntry(entExtHashTable, arrayName, EXTERNAL, instructionCounter + 1 + MEMORY_OFFSET);
        if (entry == NULL) {
            free(codeWord);
            return 1;
        }
        valueToCodeBinaryWord(0, codeWord);
        strcat(codeWord, EXTERNAL_ADD);
    } else {
        printf("\nError in line %d: undefined array name - %s\n", lineNumber ,arrayName);
        free(codeWord);
        return 1;
    }
    
    machineCodeWordsArray[instructionCounter + 1] = codeWord;
    
    /*index*/
    codeWord = (char *)malloc(sizeof(char) * WORD_SIZE + 1);
    if (codeWord == NULL) {
        printf("\nError: Memory allocation failed\n");
        return 1;
    }
    index = (int)strtol(indexStr, &endptr, 10);
    if (endptr == indexStr) {
        symbol = getEntry(symbolHashTable, indexStr);
        if (symbol == NULL) {
            printf("\nError in line %d: undefined array name - %s\n", lineNumber ,arrayName);
            free(codeWord);
            return 1;
        }
        index = symbol->value;
    }
    if (!isRepresentableBy12Bits(index)) {
        printf("\nError in line %d: Immediate value is out of range - %d\n", lineNumber, index);
        free(codeWord);
        return 1;
    }
    valueToCodeBinaryWord(index, codeWord);
    strcat(codeWord, ABSOLUTE_ADD);
    machineCodeWordsArray[instructionCounter + 2] = codeWord;

    return 0;
}


int registerToBinary(char *sourceOperand, char *destinationOperand, int instructionCounter, char *machineCodeWordsArray[]) {
    char *codeWord = NULL;
    int sourceRegNum;
    int destinationRegNum;

    codeWord = (char *)malloc(sizeof(char) * WORD_SIZE + 1);
    if (codeWord == NULL) {
        printf("\nError: Memory allocation failed\n");
        return 1;
    }

    sourceRegNum = isRegister(sourceOperand);
    destinationRegNum = isRegister(destinationOperand);

    registerBinaryWord(sourceRegNum, destinationRegNum, codeWord);


    machineCodeWordsArray[instructionCounter + 1] = codeWord;

    return 0;
}
