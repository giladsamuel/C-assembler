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


DirectiveType identifyDirectiveType(char *directive) {
    if (strcmp(directive, ".data") == 0) {
        return DATA;
    }
    if (strcmp(directive, ".string") == 0) {
        return STRING;
    }
    if (strcmp(directive, ".entry") == 0) {
        return ENTRY;
    }
    if (strcmp(directive, ".extern") == 0) {
        return EXTERN;
    }
    return -1;
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
            insertSymbolEntry(symbolHashTable, labelName, CODE, *instructionCounter);
            (*instructionCounter) += numberOfWords;
        }
        return numberOfWords;
    }
    return 0;
}



/* TODO - change if to if-else*/
int parseValidateDirective(Entry *symbolHashTable[], char *sentence, DirectiveType directiveType, int lineNumber) {
    int numberOfValues;
    if (directiveType == DATA) {
        numberOfValues = parseValidateDataDirective(symbolHashTable, sentence, lineNumber);
        if (numberOfValues == -1) {
            printf("Invalid data directive\n");
        }
    }
    if (directiveType == STRING) {
        numberOfValues = parseValidateStringDirective(sentence, lineNumber);
        if (numberOfValues == -1) {
            printf("Invalid string directive\n");
        }
    }
    if (directiveType == ENTRY) {  
        numberOfValues = parseValidateInsertEntryExternDirective(symbolHashTable, sentence, lineNumber, ENTRANCE);
        if (numberOfValues == -1) {
            printf("Invalid entry directive\n");
        }
    }
    if (directiveType == EXTERN) {
        numberOfValues = parseValidateInsertEntryExternDirective(symbolHashTable, sentence, lineNumber, EXTERNAL);
        if (numberOfValues == -1) {
            printf("Invalid extern directive\n");
        }
    }
    return numberOfValues;
}


int parseValidateDataDirective(Entry *symbolHashTable[], char *sentence, int lineNumber) {  /* TODO - move to str file */
    int numberOfValues = 0;
    char *endptr = NULL;
    char temp;
    Entry *symbol;

    if (sentence == NULL) {
        printf("\nError in line %d: Missing argument\n", lineNumber);
        return -1;
    }

    /* Skip leading whitespace */
    while (*sentence != '\0' && (*sentence == ' ' || *sentence == '\t')) {
        sentence++;
    }

    /* Check for an empty string */
    if (*sentence == '\0') {
        printf("\nError in line %d: Missing argument", lineNumber);
        return -1; 
    }

    while (*sentence != '\0' && *sentence != '\n') {
        /* Attempt to convert the next part to a double */
        strtol(sentence, &endptr, 10);
        numberOfValues++;
        /* Check if conversion was unsuccessful */
        if (endptr == sentence) {
            while (*endptr != '\0' && *endptr != ',' && *endptr != ' ' && *endptr != '\t') {
                endptr++;
            }
            temp = *endptr;
            *endptr = '\0';
            symbol = getEntry(symbolHashTable, sentence);
            if (symbol == NULL || symbol->property != MDEFINE) {
                printf("\nError in line %d: Argument '%s' is not a real number\n", lineNumber, sentence);
                return -1; /* Invalid: Failed to convert to int */
            } else {
                *endptr = temp;
            }
        }

        /* Skip trailing whitespace after the int */
        sentence = endptr;
        while (*sentence != '\0' && (*sentence == ' ' || *sentence == '\t')) {
            sentence++;
        }

        /* Check for a comma */
        if (*sentence == ',') {
            /* Move to the next character after the comma */
            sentence++;

            /* Skip trailing whitespace after the comma */
            while (*sentence != '\0' && (*sentence == ' ' || *sentence == '\t')) {
                sentence++;
            }

            /* Check if there is another comma immediately after */
            if (*sentence == ',' ) {
                printf("\nError in line %d: Multiple consecutive commas - '%s'\n", lineNumber, sentence);
                return 0; /* Invalid: Two or more commas between doubles */
            } else if (*sentence == '\0') {
                printf("\nError in line %d: Extraneous text after end of command - '%s'\n", lineNumber, sentence);
                return -1;
            }
        } else if (*sentence != '\0') {
            printf("\nError in line %d: Invalid character other than a comma or whitespace - '%s'\n", lineNumber, sentence);
            return -1; /* Invalid: Character other than a comma or whitespace */
        }
    } 
    return numberOfValues; /* Valid */
}


int parseValidateStringDirective(char *sentence, int lineNumber) {
    char *string = NULL;
    if (sentence == NULL) {
        printf("\nError in line %d: Missing argument\n", lineNumber);
        return -1;
    }
    string = strtok(sentence, " \t");
    if (string[0] != '\"') {
        printf("\nError in line %d: Missing opening quote\n", lineNumber);
        return -1;
    }
    if (string[strlen(string) - 1] != '\"') {
        printf("\nError in line %d: Missing closing quote\n", lineNumber);
        return -1;
    }
    return strlen(string) - 1; /*num of char in string without quotes with null-terminator*/
}


int parseValidateInsertEntryExternDirective(Entry *symbolHashTable[], char *sentence, int lineNumber, Property property) {
    char *name = strtok(sentence, " \t\n");
    if (name == NULL) {
        printf("\nError in line %d: Missing argument\n", lineNumber);
        return -1;
    }
    while (name != NULL) {
        if (!isValidName(symbolHashTable, name)) {
            printf("\nError in line %d: Invalid name\n", lineNumber);
            return -1;
        }
        insertSymbolEntry(symbolHashTable, name, property, 0);
        name = strtok(NULL, " \t\n");
    }
    return 0;
}


int parseValidateInstruction(char *instructionName, char* sentence, int lineNumber) {
    InstructionType instructionType;
    int numberOfOperands;
    int sourceAddressingMode;
    int destinationAddressingMode;
    int numberOfWords;


    instructionType = identifyInstructionType(instructionName);
    if (instructionType == -1) {
        printf("\nError in line %d: Invalid instruction name - '%s'\n", lineNumber, instructionName);
        return -1;
    }
    numberOfOperands = validateInstructionCommaGetNumOfOperands(sentence, lineNumber);
    if (numberOfOperands == -1) {
        printf("Error: Invalid number of commas in instruction");
        return -1;
    }
    if (!validateNumberOfOperandsAgainstInstructionType(instructionType, numberOfOperands, lineNumber)) {
        return -1;
    }
    if (!validateInstructionOperands(instructionType, sentence, &sourceAddressingMode, &destinationAddressingMode, numberOfOperands, lineNumber)) {
        return -1;
    }
    numberOfWords = getNumberOfWordsForInstruction(sourceAddressingMode, destinationAddressingMode, numberOfOperands);
    return numberOfWords;
}


/* TODO - it is general and not specific to the first*/
int isValidName(Entry * hashTable[], const char *name) {
    int i;
    if (name == NULL) {
        return 0;
    }
    if (strlen(name) > 31) {
        fprintf(stderr, "\nError: Name %s is too long.\n", name);
        return 0;
    }
    if (!isalpha(name[0])) {
        fprintf(stderr, "\nError: Name %s must start with a letter.\n", name);
        return 0;
    }
    for (i = 1; i < strlen(name); i++) {
        if (!isalnum(name[i])) {
            fprintf(stderr, "\nError: Name %s must contain only letters and digits.\n", name);
            return 0;
        }
    }
    if (getEntry(hashTable, name) != NULL) {
        fprintf(stderr, "\nError: '%s' is already defined as constant or label.\n", name);
        return 0;
    }

    return 1;
}


/* TODO - it is general and not specific to the first*/
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


Entry *insertSymbolEntry(Entry *ht[TABLE_SIZE], const char *name, int property, int value) {
    return insertEntry(ht, name, property, value, NULL);
}


int validateLabel(Entry *hashTable[], const char *label, int lineNumber) {
    if (!isValidName(hashTable, label)) {
        fprintf(stderr, "\nError: Invalid label at line %d.\n", lineNumber);
        return 0;
    }
    return 1;
}




