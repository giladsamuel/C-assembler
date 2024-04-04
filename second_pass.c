#include "second_pass.h"


int secondPass(const char* fileName, FILE *amFile, Entry *symbolHashTable[], Entry *entExtHashTable[], char *machineCodeWordsArray[]) {
    size_t len;
    char *objectFileName = NULL;
    FILE *obFile = NULL;
    char line[MAX_LINE_LENGTH];
    char lineCopy[MAX_LINE_LENGTH];
    char *firstWord = NULL;
    LineType firstWordType;
    char *sentence = NULL;
    int numberOfWords;
    int instructionCounter = 0;
    int lineNumber = 0;
    int errFlag = 0;

    objectFileName = crateJoinString(fileName, ".object");
    if (objectFileName == NULL) {
        return -1;
    }
    obFile = fopen(objectFileName, "w");
    if (obFile == NULL) {
        printf("Error: failed to open file %s\n", objectFileName);
        free(objectFileName);
        return -1;
    }
    free(objectFileName);

    rewind(amFile);

    while (fgets(line, sizeof(line), amFile) != NULL) {
        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';  /* Replace newline with null terminator */
        }
        lineNumber++;

        strncpy(lineCopy, line, sizeof(lineCopy));  /* TODO - ??It ensures that lineCopy is null-terminated even if line is not. */
        firstWord = strtok(line, " \t\n");
        firstWordType = identifyLineType(firstWord);

        if (firstWordType == EMPTY || firstWordType == COMMENT) {
            continue;
        }
        if (firstWordType == CONSTANT) {
            continue;
        }
        if (firstWordType == LABEL) {
            sentence = strtok(NULL, "");
            if (-1 == parseLabelSentence(symbolHashTable, entExtHashTable, sentence, &instructionCounter, machineCodeWordsArray, lineNumber)) 
            {
                errFlag = -1;
            }
            continue;
        }
        if (firstWordType == DIRECTIVE) {
            continue;
        }
        if (firstWordType == INSTRUCTION) {
            sentence = strtok(NULL, "");
            numberOfWords = parseInstructionToBinary(symbolHashTable, entExtHashTable, firstWord, sentence, instructionCounter, machineCodeWordsArray);
            if (numberOfWords == -1) {
                printf("Error: Invalid instruction\n"); /* TODO: malloc fail handel*/
                errFlag = -1;
            } else {
                instructionCounter += numberOfWords;
            }
            continue;
        }
    }
    return errFlag;
}


int parseLabelSentence(Entry *symbolHashTable[], Entry *entExtHashTable[], char *sentence, int *instructionCounter,  char *machineCodeWordsArray[], int lineNumber) {
    char *firstWord = NULL;
    LineType firstWordType;
    int numberOfWords = 0;

    firstWord = strtok(sentence, " \t\n");
    firstWordType = identifyLineType(firstWord);

    if (firstWordType == EMPTY || firstWordType == COMMENT || firstWordType == CONSTANT || firstWordType == LABEL || firstWordType == DIRECTIVE) {
        return 0;
    }
    if (firstWordType == INSTRUCTION) {
        sentence = strtok(NULL, "");
        numberOfWords = parseInstructionToBinary(symbolHashTable, entExtHashTable, firstWord, sentence, *instructionCounter, machineCodeWordsArray);
        if (numberOfWords == -1) {
            printf("Error: Invalid instruction\n");
        } else {
            (*instructionCounter) += numberOfWords;
        }
        return numberOfWords;
    }
    return 0;
}