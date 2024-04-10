#include "preprocessor.h"

char *addMacroLine(Entry *macroEntry, const char *line);
Entry *insertMacroEntry(Entry *ht[TABLE_SIZE], const char *name);


int preprocessMacros(const char* fileName) {
    char *asFileName = NULL;
    char *amFileName = NULL;
    FILE *asFile = NULL;
    FILE *amFile = NULL;
    char line[MAX_LINE_LENGTH + 1]; 
    char lineCopy[MAX_LINE_LENGTH + 1];
    char *firstWord = NULL;
    char *macroName = NULL;
    Entry *macroHashTable[TABLE_SIZE] = {NULL};
    Entry *macroEntry = NULL;
    Entry *newMacroEntry = NULL;
    int macroFoundFlag = 0;
    int lineNumber = 0;
    int macroErrFlag = 0;

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

    while (fgets(line, sizeof(line), asFile) != NULL) {
        lineNumber++;
        strncpy(lineCopy, line, sizeof(lineCopy));
        firstWord = strtok(lineCopy, " \t\n");
        if (firstWord == NULL) {
            fputs(line, amFile);
            continue;
        }
        macroEntry = getEntry(macroHashTable, firstWord);
        if (macroEntry != NULL) {
            fputs(macroEntry->data, amFile);
            continue;
        }

        if (strcmp(firstWord, "mcr") == 0) {
            macroFoundFlag = 1;
            macroName = strtok(NULL, " \t\n");
            if (!isValidName(macroHashTable, macroName, lineNumber)) {
                printf("ERROR in macro name\n");
                freeTable(macroHashTable);
                fclose(asFile);
                fclose(amFile);
                return 0;
            }
            newMacroEntry = insertMacroEntry(macroHashTable, macroName);
            if (newMacroEntry == NULL) {  /*memory allocation fail*/
                freeTable(macroHashTable);
                fclose(asFile);
                fclose(amFile);
                return 0;
            }
            continue;
        }

        if (macroFoundFlag) {
            if (strcmp(firstWord, "endmcr") == 0) {
                macroFoundFlag = 0;
                newMacroEntry = NULL;
            } else {

                if (addMacroLine(newMacroEntry, line) == NULL) {
                    freeTable(macroHashTable);
                    fclose(asFile);
                    fclose(amFile);
                    return 0;
                }
            }
            continue;

        } else {
            fputs(line, amFile);
        }

    }
    /* printTableEntries(macroHashTable); */
    freeTable(macroHashTable);
    fclose(asFile);
    fclose(amFile);
    return 1;
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


Entry *insertMacroEntry(Entry *ht[TABLE_SIZE], const char *name) {
    return insertEntry(ht, name, NO_PROPERTY, -1, NULL);
}
