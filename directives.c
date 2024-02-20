#include "directives.h"

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


int parseValidateDirective(Entry *symbolHashTable[], Entry *entExtHashTable[], char *sentence, DirectiveType directiveType, int lineNumber) {
    int numberOfValues;
    if (directiveType == DATA) {
        numberOfValues = parseValidateDataDirective(symbolHashTable, sentence, lineNumber);
        if (numberOfValues == -1) {
            printf("Invalid data directive\n");
        }
    }
    else if (directiveType == STRING) {
        numberOfValues = parseValidateStringDirective(sentence, lineNumber);
        if (numberOfValues == -1) {
            printf("Invalid string directive\n");
        }
    }
    else if (directiveType == ENTRY) {  
        numberOfValues = parseValidateInsertEntryExternDirective(symbolHashTable, entExtHashTable, sentence, lineNumber, ENTRANCE);
        if (numberOfValues == -1) {
            printf("Invalid entry directive\n");
        }
    }
    else if (directiveType == EXTERN) {
        numberOfValues = parseValidateInsertEntryExternDirective(symbolHashTable, entExtHashTable, sentence, lineNumber, EXTERNAL);
        if (numberOfValues == -1) {
            printf("Invalid extern directive\n");
        }
    }
    return numberOfValues;
}


int parseValidateDataDirective(Entry *symbolHashTable[], char *sentence, int lineNumber) {
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


int parseValidateInsertEntryExternDirective(Entry *symbolHashTable[], Entry *entExtHashTable[], char *sentence, int lineNumber, Property myProperty) {
    char *name = strtok(sentence, " \t\n");
    if (name == NULL) {
        printf("\nError in line %d: Missing argument\n", lineNumber);
        return -1;
    }
    while (name != NULL) {
        if (!isValidName(entExtHashTable, name, lineNumber)) {
            printf("Error: Invalid Entry/Extern name\n");
            return -1;
        if (myProperty == EXTERNAL && getEntry(symbolHashTable, name) != NULL) {
                printf("\nError in line %d: Extern '%s' already defined as symbol\n", lineNumber, name);
                return -1;
            }
        }
        insertSymbolEntExtEntry(entExtHashTable, name, myProperty, 0);
        name = strtok(NULL, " \t\n");
    }
    return 0;
}