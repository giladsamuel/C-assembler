#include "first_pass.h"


int firstPass(const char* fileName) {
    char * amFileName = NULL;
    FILE *amFile = NULL;
    char line[MAX_LINE_LENGTH]; 
    char lineCopy[MAX_LINE_LENGTH];
    char *firstWord = NULL;
    char *instruction = NULL;
    Entry *symbolHashTable[TABLE_SIZE] = {NULL};
    Entry *externHashTable[TABLE_SIZE] = {NULL};
    int instructionCounter = 0;
    int dataCounter = 0;
    int lineNumber = 0;


    amFileName = crateJoinString(fileName, ".am");

    amFile = fopen(amFileName, "r");
    if (amFile == NULL) {
        fprintf(stderr, "Error: File %s could not be opened.\n", amFileName);
        free(amFileName);
        exit(EXIT_FAILURE);
    }
    free(amFileName);

    while (fgets(line, sizeof(line), amFile) != NULL) {
        lineNumber++;

        strncpy(lineCopy, line, sizeof(lineCopy));
        firstWord = strtok(lineCopy, " \t\n");
        if (firstWord == NULL || firstWord[0] == ';') {
            continue;
        }
        if (firstWord[strlen(firstWord) - 1] == ':') {
            firstWord[strlen(firstWord) - 1] = '\0';
            instruction = strtok(NULL, " \t\n");
            insertSymbolEntry(symbolHashTable, firstWord, CODE, instructionCounter);
            firstWord = strtok(NULL, " \t\n");
        }
        if (strcmp(firstWord, ".define") == 0) {
            firstWord = strtok(NULL, " \t\n");
            insertSEntry(symbolHashTable, firstWord, MDEFINE, NULL);
            continue;
        }
        if (strcmp(firstWord, "entry") == 0) {
            firstWord = strtok(NULL, " \t\n");
            /*insertEntry(symbolHashTable, firstWord, instructionCounter, NULL);*/
            continue;
        }

        if (strcmp(firstWord, "extern") == 0) {
            firstWord = strtok(NULL, " \t\n");
            /*insertEntry(externHashTable, firstWord, 0, NULL);*/
            continue;
        }

        if (strcmp(firstWord, "data") == 0) {
            dataCounter++;
            continue;
        }

        instructionCounter++;
    }
}


Entry *insertSymbolEntry(Entry *ht[TABLE_SIZE], const char *name, int property, int value) {
    return insertEntry(ht, name, property, value, NULL);
}