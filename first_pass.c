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
    Entry *entExtHashTable[TABLE_SIZE] = {NULL};
    int instructionCounter = 0;
    int dataCounter = 0;
    int lineNumber = 0;
    int numberOfValues = 0;
    int numberOfWords = 0;
    int firstPassErrFlag = 0;

    amFileName = crateJoinString(fileName, ".am");

    amFile = fopen(amFileName, "r");
    if (amFile == NULL) {
        printf("Error: File %s could not be opened.\n", amFileName);
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
            if (parseValidateConstant(symbolHashTable, entExtHashTable, sentence, &constantName, &constantValue, lineNumber)) {
                insertSymbolEntExtEntry(symbolHashTable, constantName, MDEFINE, constantValue);
            } else {
                firstPassErrFlag = -1;
            }
            continue; /* TODO - error check not make file*/
        }
        if (firstWordType == LABEL) {
            sentence = strtok(NULL, "");
            labelName = strtok(firstWord, ":");
            if (!validateLabel(symbolHashTable, entExtHashTable, labelName, lineNumber) ||
               -1 == parseValidateLabelSentence(symbolHashTable, entExtHashTable, labelName, sentence, lineNumber, &instructionCounter, &dataCounter)) 
            {
                firstPassErrFlag = -1;
            }
            continue;
        }
        if (firstWordType == DIRECTIVE) {
            directiveType = identifyDirectiveType(firstWord);
            sentence = strtok(NULL, "");
            numberOfValues = parseValidateDirective(symbolHashTable, entExtHashTable, sentence, directiveType, lineNumber);
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

    if (firstPassErrFlag == -1) {
        printf("\nErrors in first pass.\n");
    }
    secondPass(fileName, amFile, symbolHashTable, firstPassErrFlag);
    updateDataSymbols(symbolHashTable, instructionCounter + MEMORY_OFFSET);

    printf("\nSymbol table:\n");
    printTableEntries(symbolHashTable);
    printf("\nEntry/Extern table:\n");
    printTableEntries(entExtHashTable);
    printf("\nInstruction counter: %d\n", instructionCounter);
    printf("\nData counter: %d\n", dataCounter);
    freeTable(symbolHashTable);
    freeTable(entExtHashTable);
    fclose(amFile);

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


int parseValidateConstant(Entry *symbolHashTable[], Entry *entExtHashTable[], char *sentence, char **constantName, int *constantValue, int lineNumber) {
    char *name = strtok(sentence, " \t\n");
    char *equalSign = strtok(NULL, " \t\n");
    char *value = strtok(NULL, " \t\n");
    if (!isValidName(symbolHashTable, name, lineNumber)) {
        printf("Error: Invalid constant name.\n");
        return 0;
    }
    if (getEntry(entExtHashTable, name) != NULL) {
        printf("\nError in line %d: Constant '%s' already defined as entry or extern\n", lineNumber, name);
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


int parseValidateLabelSentence(Entry *symbolHashTable[], Entry *entExtHashTable[], char *labelName, char *sentence, int lineNumber, int *instructionCounter, int *dataCounter) {
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
        numberOfValues = parseValidateDirective(symbolHashTable, entExtHashTable, sentence, directiveType, lineNumber);
        if (numberOfValues == -1) {
            printf("Invalid directive at line %d\n", lineNumber);
        }
        if (numberOfValues > 0) {
            insertSymbolEntExtEntry(symbolHashTable, labelName, DATA_STRING, *dataCounter);
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
            insertSymbolEntExtEntry(symbolHashTable, labelName, CODE, *instructionCounter + MEMORY_OFFSET);
            (*instructionCounter) += numberOfWords;
        }
        return numberOfWords;
    }
    return 0;
}


int validateLabel(Entry *symbolHashTable[], Entry *entExtHashTable[], const char *label, int lineNumber) {
    Entry *entry = NULL;
    if (!isValidName(symbolHashTable, label, lineNumber)) {
        printf("Error: Invalid label name.\n");
        return 0;
    }
    entry = getEntry(entExtHashTable, label);
    if (entry != NULL && entry->property == EXTERNAL) {
        printf("\nError in line %d: Label '%s' is already defined as external.\n", lineNumber, label);
        return 0;
    }
    return 1;
}


int isValidName(Entry *hashTable[], const char *name, int lineNumber) {
    int i;
    Entry *entry = NULL;
    if (name == NULL) {
        return 0;
    }
    if (strlen(name) > 31) {
        printf("\nError in line %d: Name '%s' is too long.\n", lineNumber, name);
        return 0;
    }
    if (!isalpha(name[0])) {
        printf("\nError in line %d: Name '%s' must start with a letter.\n", lineNumber, name);
        return 0;
    }
    for (i = 1; i < strlen(name); i++) {
        if (!isalnum(name[i])) {
            printf("\nError in line %d: Name '%s' must contain only letters and digits.\n", lineNumber, name);
            return 0;
        }
    }
    entry = getEntry(hashTable, name);
    if (entry != NULL) {
            printf("\nError in line %d: Name '%s' is already defined.\n", lineNumber, name);
            return 0;
        }

    return 1;
}


int isValidValue(const char *value) {
    int i;
    if (value == NULL) {
        return 0;
    }
    if (value[0] == '-' || value[0] == '+') {
        i = 1;
    } else {
        i = 0;
    }
    for (; i < strlen(value); i++) {
        if (!isdigit(value[i])) {
            printf("\nError: Value %s must contain only digits.\n", value);
            return 0;
        }
    }
    return 1;
}


void updateDataSymbols(Entry *symbolHashTable[], int instructionOffset) {
    int i;
    Entry *entry = NULL;
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
