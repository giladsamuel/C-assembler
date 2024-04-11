#include "preprocessor.h"

/**
 * @brief Adds a line to a macro entry.
 * 
 * This function appends a line of text to the data of a macro entry. If the macro entry's data is NULL, 
 * it allocates memory for the line and assigns it to the data. If the memory allocation fails, it prints 
 * an error message and returns NULL. If the macro entry's data is not NULL, it concatenates the line with 
 * the existing data using the crateJoinString() function, frees the old data, and assigns the new concatenated 
 * string to the data.
 * 
 * @param macroEntry The macro entry to add the line to.
 * @param line The line to be added.
 * @return The updated data of the macro entry, or NULL if memory allocation fails.
 */
char *addMacroLine(Entry *macroEntry, const char *line);


/**
 * Inserts a macro entry into the hash table.
 *
 * @param ht The hash table to insert the entry into.
 * @param name The name of the macro.
 * @return The updated hash table with the inserted entry.
 */
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
            if (!isValidMacroName(macroHashTable, macroName, lineNumber)) {
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
            printf("Error: Memory allocation failed.\n");
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


int isValidMacroName(Entry *hashTable[], const char *name, int lineNumber) {
    Entry *entry = NULL;
    if (name == NULL) {
        return 0;
    }
    if (strlen(name) > MAX_NAME_LENGTH) {
        printf("\nError in line %d: Macro name '%s' is too long.\n", lineNumber, name);
        return 0;
    }
    if (!isalpha(name[0])) {
        printf("\nError in line %d: Macro name '%s' must start with a letter.\n", lineNumber, name);
        return 0;
    }
    if (identifyDirectiveType(name) != -1 || identifyInstructionType(name) != -1) {
        printf("\nError in line %d: Macro name '%s' can not be name of instruction or directive.\n", lineNumber, name);
        return 0;
    }
    entry = getEntry(hashTable, name);
    if (entry != NULL) {
            printf("\nError in line %d: Macro name '%s' is already defined.\n", lineNumber, name);
            return 0;
        }

    return 1;
}