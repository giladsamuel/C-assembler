#include "preprocessor.h"

char *addMacroLine(Entry *macroEntry, const char *line); /* TODO - make privet*/

int preprocessMacros(const char* fileName) {  /* TODO - change func name*/
    char * asFileName = NULL;
    char * amFileName = NULL;
    FILE *asFile = NULL;
    FILE *amFile = NULL;
    char line[MAX_LINE_LENGTH]; 
    char lineCopy[MAX_LINE_LENGTH];
    char *firstWord = NULL;
    char *macroName = NULL;
    Entry *macroHashTable[TABLE_SIZE] = {NULL};
    Entry *macroEntry = NULL;
    Entry *newMacroEntry = NULL;
    int macroFound;

    asFileName = crateJoinString(fileName, ".as");
    amFileName = crateJoinString(fileName, ".am");

    asFile = fopen(asFileName, "r");
    amFile = fopen(amFileName, "w");

    if (asFile == NULL) {
        fprintf(stderr, "Error: File %s does not exist or could not be opened.\n", asFileName);
        free(asFileName);
        exit(EXIT_FAILURE);
    }
    free(amFileName);
    if (amFile == NULL) {
        fprintf(stderr, "Error: File %s could not be created.\n", amFileName);
        free(amFileName);
        exit(EXIT_FAILURE);
    }
    free(asFileName);

    macroFound = 0;
    while (fgets(line, sizeof(line), asFile) != NULL) {
        strncpy(lineCopy, line, sizeof(lineCopy));
        firstWord = strtok(lineCopy, " \t\n");

        macroEntry = getEntry(macroHashTable, firstWord);
        if (macroEntry != NULL) {
            fputs(macroEntry->data, amFile);
            continue;
        }

        if (strcmp(firstWord, "mcr") == 0) {
            macroFound = 1;
            macroName = strtok(NULL, " \t\n");
            newMacroEntry = insertEntry(macroHashTable ,macroName, 0, NULL);
            continue;
        }

        if (macroFound) {
            if (strcmp(firstWord, "endmcr") == 0) {
                macroFound = 0;
                newMacroEntry = NULL;
            } else {

                if (addMacroLine(newMacroEntry, line) == NULL) {
                    freeTable(macroHashTable);
                    fclose(asFile);
                    fclose(amFile);
                    return 1;
                }
            }
            continue;

        } else {
            fputs(line, amFile);
        }

    }
    printTableEntries(macroHashTable);  /* TODO - remove*/
    freeTable(macroHashTable);
    fclose(asFile);
    fclose(amFile);
    return 0;
}


char *addMacroLine(Entry *macroEntry, const char *line) {
    if (macroEntry->data == NULL) {
        macroEntry->data = strdup(line);
        if (macroEntry->data == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            return NULL;
        }
    } else {
        char *newData = crateJoinString(macroEntry->data, line);
        free(macroEntry->data);
        macroEntry->data = newData;
    }
    return macroEntry -> data;
}

