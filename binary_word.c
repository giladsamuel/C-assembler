#include "binary_word.h"

char *registerNumberToBinary(int registerNum);


/* 14-bit value representation*/
void valueToDataBinaryWord(int value, char binaryWord[WORD_SIZE + 1]) {
    int i;
    int isNegative = 0;
    binaryWord[WORD_SIZE] = '\0';  /* Make word null terminated*/
    if (value < 0) {
        isNegative = 1;
        value = -value;
    }
    for (i = WORD_SIZE - 1; i >= 0; i--) {
        binaryWord[i] = (value % 2) + '0';
        value /= 2;
    }
    if (isNegative) {
        for (i = WORD_SIZE - 1; i >= 0; i--) {
            binaryWord[i] = binaryWord[i] == '0' ? '1' : '0';
        }
        for (i = WORD_SIZE - 1; i >= 0; i--) {
            if (binaryWord[i] == '1') {
                binaryWord[i] = '0';
            } else {
                binaryWord[i] = '1';
                break;
            }
        }
    }
}


/* 12-bit value representation*/
void valueToCodeBinaryWord(int value, char binaryWord[WORD_SIZE + 1]) {
    int i;
    int isNegative = 0;
    binaryWord[WORD_SIZE - 2] = '\0';  /* Make word null terminated*/
    if (value < 0) {
        isNegative = 1;
        value = -value;
    }
    for (i = WORD_SIZE - 3; i >= 0; i--) {
        binaryWord[i] = (value % 2) + '0';
        value /= 2;
    }
    if (isNegative) {
        for (i = WORD_SIZE - 3; i >= 0; i--) {
            binaryWord[i] = binaryWord[i] == '0' ? '1' : '0';
        }
        for (i = WORD_SIZE - 3; i >= 0; i--) {
            if (binaryWord[i] == '1') {
                binaryWord[i] = '0';
            } else {
                binaryWord[i] = '1';
                break;
            }
        }
    }
}


int isRepresentableBy12Bits(int value) {
    return value >= TWELVE_BIT_MIN && value <= TWELVE_BIT_MAX;
}


int isRepresentableBy14Bits(int value) {
    return value >= FOURTEEN_BIT_MIN && value <= FOURTEEN_BIT_MAX;
}


int instructionFirstBinaryWord(InstructionType instructionType, int sourceAddressingMode, int destinationAddressingMode, char *codeWord, char *opcode) {
    char *sourceAddressingModeBinary = NULL;
    char *destinationAddressingModeBinary = NULL;

    sourceAddressingModeBinary = addressingModeToBinary(sourceAddressingMode);
    destinationAddressingModeBinary = addressingModeToBinary(destinationAddressingMode);
    if (sourceAddressingModeBinary == NULL || destinationAddressingModeBinary == NULL) {
        free(sourceAddressingModeBinary);
        free(destinationAddressingModeBinary);
        return 0;
    }

    strcpy(codeWord, "0000");
    strcat(codeWord, opcode);
    strcat(codeWord, sourceAddressingModeBinary);
    strcat(codeWord, destinationAddressingModeBinary);
    strcat(codeWord, ABSOLUTE_ADD);  /*‘A,R,E’*/

    free(sourceAddressingModeBinary);
    free(destinationAddressingModeBinary);

    return 1;
}


char *addressingModeToBinary(int addressingMode) {
    char *addressingModeBinary = (char *)malloc(sizeof(char) * 2 + 1);
    if (addressingModeBinary == NULL) {
        return NULL;
    }
    addressingModeBinary[2] = '\0';  /* Make word null terminated*/
    switch (addressingMode) {
        case 0:
            strcpy(addressingModeBinary, "00");
            break;
        case 1:
            strcpy(addressingModeBinary, "01");
            break;
        case 2:
            strcpy(addressingModeBinary, "10");
            break;
        case 3:
            strcpy(addressingModeBinary, "11");
            break;
        default:
            free(addressingModeBinary);
            return NULL;
    }
    return addressingModeBinary;
}


int registerBinaryWord(int sourceRegNum, int destinationRegNum, char *codeWord) {
    char *sourceRegBinary = NULL;
    char *destinationRegBinary = NULL;

    sourceRegBinary = registerNumberToBinary(sourceRegNum);
    destinationRegBinary = registerNumberToBinary(destinationRegNum);
    if (sourceRegBinary == NULL || destinationRegBinary == NULL) {
        free(sourceRegBinary);
        free(destinationRegBinary);
        return 0;
    }

    strcpy(codeWord, "000000");
    strcat(codeWord, sourceRegBinary);
    strcat(codeWord, destinationRegBinary);
    strcat(codeWord, ABSOLUTE_ADD);  /*‘A,R,E’*/

    free(sourceRegBinary);
    free(destinationRegBinary);

    return 1;
}


char *registerNumberToBinary(int registerNum) {
    char *registerNumBinary = NULL;

    registerNumBinary = (char *)malloc(sizeof(char) * 3 + 1);
    if (registerNumBinary == NULL) {
        return NULL;
    }

    if (registerNum < -1 || registerNum > 7) {
        return NULL; /* Return NULL if registerNum is out of range */
    }

    if (registerNum == -1) {
        strcpy(registerNumBinary, "000");  /* -1 indicates that operand isn't a register */
        return registerNumBinary; 
    }
    
    /* Convert registerNum to binary representation */
    registerNumBinary[0] = (registerNum & 4) ? '1' : '0';   /* 4 = 0b100*/
    registerNumBinary[1] = (registerNum & 2) ? '1' : '0';   /* 2 = 0b010*/
    registerNumBinary[2] = (registerNum & 1) ? '1' : '0';   /* 1 = 0b001*/
    registerNumBinary[3] = '\0'; /* Null-terminate the string */
    
    return registerNumBinary;
}


void printBinaryWordsArray(char *wordsArray[], int counter) {
    int i;
    for (i = 0; i < counter; i++) {
        printf("%s\n", wordsArray[i]);
    }
}


void freeBinaryWordsArray(char *wordsArray[], int counter) {
    int i;
    for (i = 0; i < counter; i++) {
        free(wordsArray[i]);
    }
}


int binaryToDecimal(char *binary) {
    return (int)strtol(binary, NULL, 2);
}