#include "output_files.h"

int createOutputFiles(const char *fileName, FILE *amFile, int IC, int DC, char *machineCodeWordsArray[], char *dataWordsArray[], Entry *entExtHashTable[]) {
    char *objectFileName = NULL;
    FILE *obFile = NULL;

    objectFileName = crateJoinString(fileName, ".ob");
    if (objectFileName == NULL) {
        return 0;
    }
    obFile = fopen(objectFileName, "w");
    if (obFile == NULL) {
        printf("Error: failed to open file %s\n", objectFileName);
        free(objectFileName);
        return 0;
    }
    free(objectFileName);

    writeObjectFile(obFile, IC, DC, machineCodeWordsArray, dataWordsArray);
    fclose(obFile);

    /*isThereEntrance(entExtHashTable);*/

    
    return 1;
}


void writeObjectFile(FILE *obFile, int IC, int DC, char *machineCodeWordsArray[], char *dataWordsArray[]) {
    int i;
    int lineNum = 100;
    char encryptLine[8];

    fprintf(obFile, "%4d %d", IC, DC);
    for (i = 0; i < IC; i++, lineNum++) {
        encryptWord(encryptLine ,machineCodeWordsArray[i]);
        fprintf(obFile, "\n%04d %s", lineNum, encryptLine);
    }
    for (i = 0; i < DC ; i++, lineNum++) {
        encryptWord(encryptLine, dataWordsArray[i]);
        fprintf(obFile, "\n%04d %s", lineNum, encryptLine);
    }
}


void encryptWord(char encryptLine[8], char *binaryWord) {
    int i;
    int decimal;
    char base4Char;
    char chunk[3];

    for (i = 0; i < 7; i++) {
        strncpy(chunk, binaryWord + (i * 2), 2);
        chunk[2] = '\0';

        decimal = binaryToDecimal(chunk);
        base4Char = mapToBase4(decimal);
        encryptLine[i] = base4Char;
    }

    encryptLine[7] = '\0';
}


int binaryToDecimal(char *binary) {
    return (int)strtol(binary, NULL, 2);
}


char mapToBase4(int decimal) {
    char base4[] = {'*', '#', '%', '!'};

    return base4[decimal];
}

