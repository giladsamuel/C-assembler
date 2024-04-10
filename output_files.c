#include "output_files.h"

int createOutputFiles(const char *fileName, int IC, int DC, char *machineCodeWordsArray[], char *dataWordsArray[], Entry *entExtHashTable[]) {
    FILE *obFile = NULL;
    FILE *entFile = NULL;
    FILE *extFile = NULL;
    
    obFile = creatOpenFile(fileName, ".ob");
    if (obFile == NULL) {
        printf("Error: failed to open file %s.ob\n", fileName);
        return 0;
    }
    writeObjectFile(obFile, IC, DC, machineCodeWordsArray, dataWordsArray);
    fclose(obFile);

    if(isThereEntExt(entExtHashTable, ENTRANCE)) {
        entFile = creatOpenFile(fileName, ".ent");
        if (entFile == NULL) {
            printf("Error: failed to open file %s.ent\n", fileName);
            return 0;
        }
        writeEntExtFile(entFile, entExtHashTable,  ENTRANCE);
        fclose(entFile);
    }

    if(isThereEntExt(entExtHashTable, EXTERNAL)) {
        extFile = creatOpenFile(fileName, ".ext");
        if (extFile == NULL) {
            printf("Error: failed to open file %s.ext\n", fileName);
            return 0;
        }

        writeEntExtFile(extFile, entExtHashTable, EXTERNAL);
        fclose(extFile);
    }

    return 1;
}


FILE *creatOpenFile(const char *fileName, char *fileExtention) {
    char *newFileName = NULL;
    FILE *file = NULL;

    newFileName = crateJoinString(fileName, fileExtention);
    if (newFileName == NULL) {
        return NULL;
    }
    file = fopen(newFileName, "w");
    if (file == NULL) {
        printf("Error: failed to open file %s\n", newFileName);
        free(newFileName);
        return NULL;
    }
    free(newFileName);

    return file;
}


void writeObjectFile(FILE *obFile, int IC, int DC, char *machineCodeWordsArray[], char *dataWordsArray[]) {
    int i;
    int lineNum = MEMORY_OFFSET;
    char encryptLine[8];

    fprintf(obFile, "%4d %d", IC, DC);
    for (i = 0; i < IC; i++, lineNum++) {
        encryptWord(encryptLine ,machineCodeWordsArray[i]);
        fprintf(obFile, "\n%04d %s", lineNum, encryptLine);
    }
    for (i = 0; i < DC ; i++, lineNum++) {
        encryptWord(encryptLine, dataWordsArray[i]);
        fprintf(obFile, "\n%04d %s", lineNum, encryptLine);
    }
}


void writeEntExtFile(FILE *entExtFile, Entry *entExtHashTable[], Property propertyType) {
    int i;
    Entry *entry;

    for (i = 0; i < TABLE_SIZE; i++) {
        entry = entExtHashTable[i];
        while (entry != NULL) {
            if (entry->property == propertyType && entry->value != 0) {
                fprintf(entExtFile, "%s\t%04d\n", entry->name, entry->value);
            }
            entry = entry->next;
        }
    }
}


void encryptWord(char encryptLine[8], char *binaryWord) {
    int i;
    int decimal;
    char base4Char;
    char chunk[3];

    for (i = 0; i < 7; i++) {
        strncpy(chunk, binaryWord + (i * 2), 2);
        chunk[2] = '\0';

        decimal = binaryToDecimal(chunk);
        base4Char = mapToBase4(decimal);
        encryptLine[i] = base4Char;
    }

    encryptLine[7] = '\0';
}


char mapToBase4(int decimal) {
    char base4[] = {'*', '#', '%', '!'};

    return base4[decimal];
}


int isThereEntExt(Entry *entExtHashTable[], Property propertyType) {
    int i;
    Entry *entry;

    for (i = 0; i < TABLE_SIZE; i++) {
        entry = entExtHashTable[i];
        while (entry != NULL) {
            if (entry->property == propertyType) {
                return 1;
            }
            entry = entry->next;
        }
    }

    return 0;
}