#include "binary_word.h"

void dataToBinaryWord(int data, char binaryWord[WORD_SIZE + 1]) {
    int i;
    int isNegative = 0;
    binaryWord[WORD_SIZE] = '\0';  /* Make word null terminated*/
    if (data < 0) {
        isNegative = 1;
        data = -data;
    }
    for (i = WORD_SIZE - 1; i >= 0; i--) {
        binaryWord[i] = (data % 2) + '0';
        data /= 2;
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

/*
void stringToBinaryWords(char *string, char *binaryWord) {
    int i;
    for (i = 0; i < WORD_SIZE; i++) {
        binaryWord[i] = '0';
    }
    for (i = 0; i < strlen(string); i++) {
        charToBinaryWord(string[i], binaryWord + i * 8);
    }
}*/

void printBinaryWordsArray(char *dataWordsArray[], int dataCounter) {
    int i;
    for (i = 0; i < dataCounter; i++) {
        printf("%s\n", dataWordsArray[i]);
    }
}

void freeBinaryWordsArray(char *dataWordsArray[], int dataCounter) {
    int i;
    for (i = 0; i < dataCounter; i++) {
        free(dataWordsArray[i]);
    }
}