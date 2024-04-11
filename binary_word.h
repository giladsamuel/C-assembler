#ifndef BINARY_WORD_H
#define BINARY_WORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instruction_type.h"

#define WORD_SIZE 14

#define FOURTEEN_BIT_MIN -8192
#define FOURTEEN_BIT_MAX 8191

#define TWELVE_BIT_MIN -2048
#define TWELVE_BIT_MAX 2047

/**
 * Converts a given integer value to a binary word representation.
 * 14-bit value representation
 * 
 * @param value The integer value to be converted.
 * @param binaryWord The character array to store the binary word representation.
 */
void valueToDataBinaryWord(int value, char binaryWord[WORD_SIZE + 1]);


/**
 * Converts a given integer value to a binary word representation.
 * 12-bit value representation
 * 
 * @param value The integer value to be converted.
 * @param binaryWord The character array to store the binary word representation.
 */
void valueToCodeBinaryWord(int value, char binaryWord[WORD_SIZE + 1]);


/**
 * Checks if the given value can be represented by 12 bits.
 *
 * @param value The value to be checked.
 * @return 1 if the value can be represented by 12 bits, 0 otherwise.
 */
int isRepresentableBy12Bits(int value);


/**
 * Checks if a given value can be represented by 14 bits.
 *
 * @param value The value to be checked.
 * @return 1 if the value is representable by 14 bits, 0 otherwise.
 */
int isRepresentableBy14Bits(int value);


/**
 * @brief Generates the first binary word of an instruction.
 *
 * This function takes an instruction type, source addressing mode, destination addressing mode,
 * code word, and opcode as input parameters. It generates the first binary word of the instruction
 * by converting the addressing modes to binary representation and concatenating them with the opcode
 * and other necessary bits. The resulting binary word is stored in the code word parameter.
 *
 * @param instructionType The type of the instruction.
 * @param sourceAddressingMode The addressing mode of the source operand.
 * @param destinationAddressingMode The addressing mode of the destination operand.
 * @param codeWord The buffer to store the generated binary word.
 * @param opcode The opcode of the instruction.
 * @return 1 if the binary word is generated successfully, 0 otherwise.
 */
int instructionFirstBinaryWord(InstructionType instructionType, int sourceAddressingMode, int destinationAddressingMode, char *machineCodeWord, char *opcode);


/**
 * Converts an addressing mode to its binary representation.
 *
 * @param addressingMode The addressing mode to convert.
 * @return The binary representation of the addressing mode as a dynamically allocated string.
 *         Returns NULL if memory allocation fails or if the addressing mode is invalid.
 */
char *addressingModeToBinary(int addressingMode);


/**
 * @brief Make a binary word with the given source and destination register numbers.
 * 
 * This function converts the source and destination register numbers to binary representation
 * and combines them with a predefined code word to form the final binary word. The binary word
 * is stored in the provided codeWord buffer.
 * 
 * @param sourceRegNum The source register number.
 * @param destinationRegNum The destination register number.
 * @param codeWord The buffer to store the binary word.
 * @return 1 if the binary word is successfully registered, 0 otherwise.
 */
int registerBinaryWord(int sourceRegNum, int destinationRegNum, char *codeWord);


/**
 * Converts a register number to its binary representation.
 *
 * @param registerNum The register number to convert.
 * @return A dynamically allocated string containing the binary representation of the register number.
 *         Returns NULL if the register number is out of range or if memory allocation fails.
 */
char *registerNumberToBinary(int registerNum);


/**
 * Prints an array of binary words.
 *
 * This function takes an array of binary words and the number of words in the array,
 * and prints each word on a new line.
 *
 * @param wordsArray The array of binary words.
 * @param counter The number of words in the array.
 */
void printBinaryWordsArray(char *dataWordsArray[], int dataCounter);


/**
 * Frees the memory allocated for an array of binary words.
 * 
 * @param wordsArray The array of binary words.
 * @param counter The number of words in the array.
 */
void freeBinaryWordsArray(char *dataWordsArray[], int dataCounter);


/**
 * Converts a binary string to its decimal representation.
 *
 * @param binary The binary string to be converted.
 * @return The decimal representation of the binary string.
 */
int binaryToDecimal(char *binary);

#endif