#include "binary_word.h"


void valueToBinaryWord(int value, char binaryWord[WORD_SIZE + 1]) {
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