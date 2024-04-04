#ifndef INSTRUCTION_TYPE_H
#define INSTRUCTION_TYPE_H

/*‘A,R,E’*/
#define ABSOLUTE_ADD    "00"
#define EXTERNAL_ADD    "01"
#define RELOCATABLE_ADD "10"

typedef enum {
    MOV,
    CMP,
    ADD,
    SUB,
    NOT,
    CLR,
    LEA,
    INC,
    DEC,
    JMP,
    BNE,
    RED,
    PRN,
    JSR,
    RTS,
    HLT
} InstructionType;

#endif 