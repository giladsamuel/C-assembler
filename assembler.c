#include <stdio.h>
#include <stdlib.h>
#include "str_helper.h"
#include "preprocessor.h"
#include "first_pass.h"


/**
 * @file assembler.c
 * @brief This file contains the main function for the assembler program.
 *
 * The assembler program takes assembly code as input and converts it into encrypted machine code.
 * It reads the assembly code from a file specified as a command line argument.
 * The resulting machine code is written to output files with the same name as the input file, but with different extensions.
 * The program supports various assembly instructions and directives.
 * It also performs error checking and reports any syntax errors or invalid instructions.
 */

int main(int argc, const char *argv[]) {
    int i;
    
    if (argc <= 1) {
        printf("No command line file name arguments provided.\n");
        return 1;
    }
    for (i = 1; i < argc; i++) {

        printf("Argument %d: %s\n", i, argv[i]);
        if (NOT preprocessMacros(argv[i])) {
            printf("Error: Fail in macro preprocessor.\n");
            continue;
        }
        firstPass(argv[i]);
    }

    return EXIT_SUCCESS;
}
