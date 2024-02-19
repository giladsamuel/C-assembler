#include "first_pass.h"


int firstPass(const char* fileName) {
    size_t len;
    char * amFileName = NULL;
    FILE *amFile = NULL;
    char line[MAX_LINE_LENGTH]; 
    char lineCopy[MAX_LINE_LENGTH];
    char *firstWord = NULL;
    LineType firstWordType;
    DirectiveType directiveType;
    char *sentence = NULL;
    char *constantName = NULL;
    int constantValue;
    char *labelName = NULL;
    Entry *symbolHashTable[TABLE_SIZE] = {NULL};
    int instructionCounter = 0;
    int dataCounter = 0;
    int lineNumber = 0;
    int numberOfValues = 0;
    int numberOfWords = 0;
    int firstPassErrFlag = 0;

    amFileName = crateJoinString(fileName, ".am");

    amFile = fopen(amFileName, "r");
    if (amFile == NULL) {
        fprintf(stderr, "Error: File %s could not be opened.\n", amFileName);
        free(amFileName);
        exit(EXIT_FAILURE);
    }
    free(amFileName);

    while (fgets(line, sizeof(line), amFile) != NULL) {
        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';  /* Replace newline with null terminator */
        }
        lineNumber++;

        strncpy(lineCopy, line, sizeof(lineCopy));  /* TODO - ??It ensures that lineCopy is null-terminated even if line is not. */
        firstWord = strtok(lineCopy, " \t\n");
        firstWordType = identifyLineType(firstWord);

        if (firstWordType == EMPTY || firstWordType == COMMENT) {
            continue;
        }
        if (firstWordType == CONSTANT) {
            sentence = strtok(NULL, "");
            if (parseValidateConstant(symbolHashTable, sentence, &constantName, &constantValue, lineNumber)) {
                insertSymbolEntry(symbolHashTable, constantName, MDEFINE, constantValue);
            } else {
                firstPassErrFlag = -1;
            }
            continue; /* TODO - error check not make file*/
        }
        if (firstWordType == LABEL) {
            sentence = strtok(NULL, "");
            labelName = strtok(firstWord, ":");
            if (!validateLabel(symbolHashTable, labelName, lineNumber) ||
               -1 == parseValidateLabelSentence(symbolHashTable, labelName, sentence, lineNumber, &instructionCounter, &dataCounter)) 
            {
                firstPassErrFlag = -1;
            }
            continue;
        }
        if (firstWordType == DIRECTIVE) {
            directiveType = identifyDirectiveType(firstWord);
            sentence = strtok(NULL, "");
            numberOfValues = parseValidateDirective(symbolHashTable, sentence, directiveType, lineNumber);
            if (numberOfValues > 0) {
                dataCounter += numberOfValues;  /* TODO - handel error*/
            } else if (numberOfValues == -1) {
                firstPassErrFlag = -1;
            }
            continue;
        }
        if (firstWordType == INSTRUCTION) {
            sentence = strtok(NULL, "");
            numberOfWords = parseValidateInstruction(firstWord, sentence, lineNumber);
            if (numberOfWords == -1) {
                printf("Error: Invalid instruction\n");
                firstPassErrFlag = -1;
            } else {
                instructionCounter += numberOfWords;
            }
            continue;
        }
    }
    updateDataSymbols(symbolHashTable, instructionCounter + MEMORY_OFFSET);
    printTableEntries(symbolHashTable);
    fclose(amFile);
    printf("Instruction counter: %d\n", instructionCounter);
    printf("Data counter: %d\n", dataCounter);
    return firstPassErrFlag;
}


LineType identifyLineType(char *word) {
    if (word == NULL) {
        return EMPTY;
    }
    if (word[0] == ';') {
        return COMMENT;
    }
    if (word[strlen(word) - 1] == ':') {
        return LABEL;
    }
    if (strcmp(word, ".define") == 0) {
        return CONSTANT;
    }
    if (word[0] == '.') {
        return DIRECTIVE;
    }
    return INSTRUCTION;
}





int parseValidateConstant(Entry *hashTable[], char *sentence, char **constantName, int *constantValue, int lineNumber) {
    char *name = strtok(sentence, " \t\n");
    char *equalSign = strtok(NULL, " \t\n");
    char *value = strtok(NULL, " \t\n");
    if (!isValidName(hashTable, name)) {
        printf("\nError: Invalid constant name at line %d.\n", lineNumber);
        return 0;
    }
    if (equalSign == NULL || *equalSign != '=' ) {
        printf("\nError: Invalid constant definition at line %d.\n", lineNumber);
        return 0;
    }
    if (!isValidValue(value)) {
        printf("\nError: Invalid constant value at line %d.\n", lineNumber);
        return 0;
    }
    *constantName = name;
    *constantValue = atoi(value);
    return 1;
}


int parseValidateLabelSentence(Entry *symbolHashTable[], char *labelName, char *sentence, int lineNumber, int *instructionCounter, int *dataCounter) {
    char *firstWord = NULL;
    LineType firstWordType;
    DirectiveType directiveType;
    int numberOfValues = 0;
    int numberOfWords = 0;

    firstWord = strtok(sentence, " \t\n");
    firstWordType = identifyLineType(firstWord);

    if (firstWordType == EMPTY || firstWordType == COMMENT) {
        printf("\nError in line %d: Empty or comment line after a label is prohibited\n", lineNumber);
        return -1;
    }
    if (firstWordType == CONSTANT) {
        printf("\nError in line %d: Define constant after a label is prohibited\n", lineNumber);
        return -1;
    }
    if (firstWordType == LABEL) {
        printf("\nError in line %d: Label after a label is prohibited\n", lineNumber);
        return -1;
    }
    if (firstWordType == DIRECTIVE) {
        directiveType = identifyDirectiveType(firstWord);
        if (directiveType == ENTRY || directiveType == EXTERN) {
            printf("\nWarning in line %d: Label before entry or extern is meaningless\n", lineNumber);
        }
        sentence = strtok(NULL, "");
        numberOfValues = parseValidateDirective(symbolHashTable, sentence, directiveType, lineNumber);
        if (numberOfValues == -1) {
            printf("Invalid directive at line %d\n", lineNumber);
        }
        if (numberOfValues > 0) {
            insertSymbolEntry(symbolHashTable, labelName, DATA_STRING, *dataCounter);
            (*dataCounter) += numberOfValues;
        }
        return numberOfValues;
    }
    if (firstWordType == INSTRUCTION) {
        sentence = strtok(NULL, "");
        numberOfWords = parseValidateInstruction(firstWord, sentence, lineNumber);
        if (numberOfWords == -1) {
            printf("Error: Invalid instruction\n");
        } else {
            insertSymbolEntry(symbolHashTable, labelName, CODE, *instructionCounter + MEMORY_OFFSET);
            (*instructionCounter) += numberOfWords;
        }
        return numberOfWords;
    }
    return 0;
}












int validateLabel(Entry *hashTable[], const char *label, int lineNumber) {
    if (!isValidName(hashTable, label)) {
        fprintf(stderr, "\nError: Invalid label at line %d.\n", lineNumber);
        return 0;
    }
    return 1;
}


void updateDataSymbols(Entry *symbolHashTable[], int instructionOffset) {
    int i;
    Entry *entry;
    for (i = 0; i < TABLE_SIZE; i++) {
        entry = symbolHashTable[i];
        while (entry != NULL) {
            if (entry->property == DATA_STRING) {
                entry->value += instructionOffset;
            }
            entry = entry->next;
        }
    }
    
}


