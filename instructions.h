#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "binary_word.h"
#include "instruction_type.h"
#include "hash_table.h"


enum {
    NO_OPERAND,
    ALL,
    NO_NUMBER,
    LABEL_INDEX,
    LABEL_REGISTER
} ;

enum {
    IMMEDIATE,
    DIRECT,
    INDEX_ARRAY,
    REGISTER
};


/**
 * Parses and validates an instruction.
 *
 * This function takes an instruction name, a sentence, and a line number as input.
 * It identifies the type of the instruction, validates the number of operands,
 * validates the operands themselves, and calculates the number of words required
 * for the instruction. If any validation fails, an error message is printed and
 * -1 is returned. Otherwise, the number of words is returned.
 *
 * @param instructionName The name of the instruction.
 * @param sentence The sentence containing the instruction and its operands.
 * @param lineNumber The line number where the instruction is located.
 * @return The number of words required for the instruction, or -1 if an error occurs.
 */
int parseValidateInstruction(char *instructionName, char* sentence, int lineNumber);


/**
 * Identifies the type of instruction based on the given instruction name.
 *
 * @param instructionName The name of the instruction.
 * @return The type of instruction, or -1 if the instruction name is invalid.
 */
int identifyInstructionType(const char *instructionName);


/**
 * Validates an instruction and returns the number of operands.
 * 
 * @param sentence The instruction sentence to validate.
 * @param lineNumber The line number of the instruction.
 * @return The number of operands if the instruction is valid, -1 otherwise.
 */
int validateInstructionCommaGetNumOfOperands(char *sentence, int lineNumber);


/**
 * Validates the number of operands against the instruction type.
 * 
 * @param instructionType The type of the instruction.
 * @param numberOfOperands The number of operands.
 * @param lineNumber The line number of the instruction.
 * @return Returns 1 if the number of operands is valid, otherwise returns 0.
 */
int validateNumberOfOperandsAgainstInstructionType(InstructionType instructionType, int numberOfOperands, int lineNumber);


/**
 * Validates the operands of an instruction.
 *
 * This function takes an instruction type, a sentence containing the operands,
 * the addressing modes of the source and destination operands, the number of operands,
 * and the line number of the instruction. It validates the operands based on the
 * instruction type, gets the addressing mode and returns a result indicating whether the operands are valid or not.
 *
 * @param instructionType The type of the instruction.
 * @param sentence The sentence containing the operands.
 * @param sourceAddressingMode A pointer to the variable storing the addressing mode of the source operand.
 * @param destinationAddressingMode A pointer to the variable storing the addressing mode of the destination operand.
 * @param numberOfOperands The number of operands.
 * @param lineNumber The line number of the instruction.
 * @return 1 if the operands are valid, -1 otherwise.
 */
int validateInstructionOperands(InstructionType instructionType, char *sentence, int *sourceAddressingMode, int *destinationAddressingMode,  int numberOfOperands, int lineNumber);


/**
 * Identifies the addressing mode of an operand.
 *
 * @param operand The operand to be analyzed.
 * @return The addressing mode of the operand:
 *         - IMMEDIATE if the operand starts with '#'
 *         - INDEX_ARRAY if the operand is an index array
 *         - REGISTER if the operand is a register
 *         - DIRECT if none of the above conditions are met
 *         - -1 if the operand is NULL
 */
int identifyAddressingMode(char *operand);


/**
 * Checks if the given operand is a valid register.
 * A valid register is a string that starts with 'r' followed by a single digit between 0 and 7.
 *
 * @param operand The operand to check.
 * @return The register number if the operand is a valid register, -1 otherwise.
 */
int isRegister(char *operand);


/**
 * Checks if the given operand is an index array.
 * An index array is defined as a string that ends with ']', contains at least one '[' character,
 * and does not contain any whitespace characters between the '[' and ']'.
 * The index defined as the element between the '[' and ']'.
 * 
 * @param operand The operand to check.
 * @return 1 if the operand is an index array, 0 otherwise.
 */
int isIndexArray(char *operand);


/**
 * Validates the destination addressing mode against the instruction type.
 * 
 * @param instructionType The type of the instruction.
 * @param addressingMode The addressing mode to validate.
 * @param lineNumber The line number of the instruction.
 * @return Returns 1 if the destination addressing mode is valid, otherwise returns 0.
 */
int validateDestinationAddressingModeAgainstInstructionType(InstructionType instructionType, int addressingMode, int lineNumber);


/**
 * Validates the source addressing mode against the instruction type.
 *
 * @param instructionType The type of the instruction.
 * @param addressingMode The addressing mode to validate.
 * @param lineNumber The line number of the instruction.
 * @return 1 if the source addressing mode is valid, 0 otherwise.
 */
int validateSourceAddressingModeAgainstInstructionType(InstructionType instructionType, int addressingMode, int lineNumber);


/**
 * Calculates the number of words required for an instruction based on the addressing modes and number of operands.
 *
 * @param sourceAddressingMode The addressing mode of the source operand.
 * @param destinationAddressingMode The addressing mode of the destination operand.
 * @param numberOfOperands The number of operands in the instruction.
 * @return The number of words required for the instruction. Returns -1 if the number of operands is invalid.
 */
int getNumberOfWordsForInstruction(int sourceAddressingMode, int destinationAddressingMode, int numberOfOperands);


/**
 * Parses an instruction into binary representation.
 *
 * @param symbolHashTable The symbol hash table.
 * @param entExtHashTable The entry/external hash table.
 * @param instructionName The name of the instruction.
 * @param sentence The instruction sentence.
 * @param instructionCounter The instruction counter.
 * @param machineCodeWordsArray The array to store the machine code words.
 * @param lineNumber The line number of the instruction.
 * @return The number of binary words generated for the instruction.
 */
int parseInstructionToBinary(Entry *symbolHashTable[], Entry *entExtHashTable[], char *instructionName, char *sentence, int instructionCounter, char *machineCodeWordsArray[], int lineNumber);


/**
 * @brief Retrieves the operands and addressing modes for an instruction.
 *
 * This function parses a sentence and extracts the first and second operands,
 * as well as the addressing modes for the source and destination operands.
 *
 * @param firstOperandP Pointer to store the first operand.
 * @param secondOperandP Pointer to store the second operand.
 * @param sentence The sentence to parse.
 * @param sourceAddressingMode Pointer to store the addressing mode of the source operand.
 * @param destinationAddressingMode Pointer to store the addressing mode of the destination operand.
 * @param numberOfOperands The number of operands for the instruction.
 * @return 1 if the operands and addressing modes were successfully retrieved, -1 otherwise.
 */
int getInstructionOperands(char **firstOperandP, char **secondOperandP, char *sentence, int *sourceAddressingMode, int *destinationAddressingMode,  int numberOfOperands);


/**
 * Calculates the number of binary words required to represent an instruction and create them based on the given parameters.
 *
 * @param symbolHashTable The symbol hash table.
 * @param entExtHashTable The entry/external hash table.
 * @param numberOfOperands The number of operands in the instruction.
 * @param firstOperand The first operand.
 * @param secondOperand The second operand.
 * @param sourceAddressingMode The addressing mode of the source operand.
 * @param destinationAddressingMode The addressing mode of the destination operand.
 * @param instructionCounter The instruction counter.
 * @param machineCodeWordsArray The array to store the machine code words.
 * @param lineNumber The line number of the instruction.
 * @return The number of binary words required to represent the instruction, or -1 if an error occurred.
 */
int getInstructionBinaryWords(Entry *symbolHashTable[], Entry *entExtHashTable[], int numberOfOperands, char *firstOperand, char *secondOperand, int sourceAddressingMode, int destinationAddressingMode, int instructionCounter, char *machineCodeWordsArray[], int lineNumber);


/**
 * Converts an immediate operand to binary representation and stores it in the machine code words array.
 * 
 * @param symbolHashTable The symbol hash table.
 * @param operand The immediate operand.
 * @param instructionCounter The current instruction counter.
 * @param machineCodeWordsArray The machine code words array.
 * @param lineNumber The line number of the instruction.
 * @return 0 if successful, 1 if an error occurred.
 */
int immediateToBinary(Entry *symbolHashTable[], char *operand, int instructionCounter, char *machineCodeWordsArray[], int lineNumber);


/**
 * Converts an direct operand to binary representation and stores it in the machine code words array.
 * @param symbolHashTable The symbol hash table.
 * @param entExtHashTable The entry/external hash table.
 * @param operandLabel The operand label to convert.
 * @param instructionCounter The current instruction counter.
 * @param machineCodeWordsArray The array to store the binary code words.
 * @param lineNumber The line number of the instruction.
 * @return 0 if successful, 1 if memory allocation failed or an error occurred.
 */
int directToBinary(Entry *symbolHashTable[], Entry *entExtHashTable[], char *operandLabel, int instructionCounter, char *machineCodeWordsArray[], int lineNumber);


/**
 * Converts an index array operand to binary representation and stores it in the machine code words array.
 * @param symbolHashTable The symbol hash table.
 * @param entExtHashTable The entry/external hash table.
 * @param operand The operand of the instruction.
 * @param instructionCounter The current instruction counter.
 * @param machineCodeWordsArray The array to store the machine code words.
 * @param lineNumber The line number of the instruction.
 * @return 0 if successful, 1 if an error occurred.
 */
int indexArrayToBinary(Entry *symbolHashTable[], Entry *entExtHashTable[], char *operand, int instructionCounter, char *machineCodeWordsArray[], int lineNumber);


/**
 * Converts the source and destination register operands to binary and stores the result in the machine code words array.
 *
 * @param sourceOperand The source operand to convert.
 * @param destinationOperand The destination operand to convert.
 * @param instructionCounter The current instruction counter.
 * @param machineCodeWordsArray The array to store the binary code words.
 * @return 0 if successful, 1 if memory allocation failed.
 */
int registerToBinary(char *sourceOperand, char *destinationOperand, int instructionCounter, char *machineCodeWordsArray[]);

#endif