#include "macro.h"
#include "str_helper.h"

int macroToTable(const char* fileName) {  /* TODO - change func name*/
    char * asFileName = NULL;
    char * amFileName = NULL;
    FILE *asFile = NULL;
    FILE *amFile = NULL;
    char line[MAX_LINE_LENGTH]; 
    char lineCopy[MAX_LINE_LENGTH];
    char *linePtr = line;  /* todo - delete?*/
    char *word = NULL;
    char *macroName = NULL;
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
        word = strtok(lineCopy, " \t\n");
        if (word == NULL) {
            continue;
        }
        if (word[0] == ';') {
            continue;
        }
        if (isInMacroTable(word)) { /* TODO */
            
        }

        if (strcmp(word, "mcr") == 0) {
            macroFound = 1;

            macroName = strtok(NULL, " \t\n");


            addMacroToTable(macroName);
            continue;
        }

        if (macroFound) {
            if (strcmp(word, "endmcr") == 0) {
                macroFound = 0;
            } else {
                addMacroLine(macroName, line);
            }
            continue;

        } else {
            fputs(line, amFile);
        }

    }
    fclose(asFile);
    fclose(amFile);
    return 0;
}