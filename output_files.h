#ifndef OUTPUT_FILES_h
#define OUTPUT_FILES_h

#include <stdio.h>

#include "hash_table.h"
#include "binary_word.h"


/**
 * Creates output files for the given assembly program.
 *
 * @param fileName The name of the assembly program file.
 * @param IC The value of the instruction counter.
 * @param DC The value of the data counter.
 * @param machineCodeWordsArray An array of machine code words.
 * @param dataWordsArray An array of data words.
 * @param entExtHashTable An array of Entry structures representing the entry and external symbols.
 * @return 1 if the output files are created successfully, 0 otherwise.
 */
int createOutputFiles(const char *fileName, int IC, int DC, char *machineCodeWordsArray[], char *dataWordsArray[], Entry *entExtHashTable[]);


/**
 * @brief Creates and opens a file with the given file name and extension.
 * 
 * This function takes a file name and extension as input and creates a new file with the specified name and extension.
 * The file is opened in write mode. If the file creation and opening is successful, a pointer to the opened file is returned.
 * If any error occurs during file creation or opening, NULL is returned.
 * 
 * @param fileName The name of the file.
 * @param fileExtension The extension of the file.
 * @return A pointer to the opened file if successful, NULL otherwise.
 */
FILE *creatOpenFile(const char *fileName, char *fileExtention);


/**
 * Writes the object file with the given machine code and data words arrays.
 * 
 * @param obFile The file pointer to the object file.
 * @param IC The instruction counter value.
 * @param DC The data counter value.
 * @param machineCodeWordsArray The array of machine code words.
 * @param dataWordsArray The array of data words.
 */
void writeObjectFile(FILE *obFile, int IC, int DC, char *machineCodeWordsArray[], char *dataWordsArray[]);


/**
 * Writes .ent/.ext file with entry/extern values from the entExtHashTable,
 * base on the given property type and non-zero value to a file.
 *
 * @param entExtFile The file to write the entries to.
 * @param entExtHashTable The hash table containing the entry's and externs.
 * @param propertyType The property type to filter the entries by.
 */
void writeEntExtFile(FILE *entFile, Entry *entExtHashTable[], Property propertyType);


/**
 * Encrypts a word represented in binary format and stores the encrypted result in the given encryptLine array.
 * 
 * @param encryptLine The array to store the encrypted word.
 * @param binaryWord The binary representation of the word to be encrypted.
 */
void encryptWord(char encryptLine[8], char *binaryWord);


/**
 * Maps a decimal number to a base 4 character.
 *
 * @param decimal The decimal number to be mapped.
 * @return The base 4 character corresponding to the decimal number.
 */
char mapToBase4(int decimal);


/**
 * Checks if a specific property type exists in the entExtHashTable.
 *
 * @param entExtHashTable The hash table containing the entries.
 * @param propertyType The property type to search for.
 * @return 1 if the property type exists, 0 otherwise.
 */
int isThereEntExt(Entry *entExtHashTable[], Property propertyType);

#endif