#include <stdio.h>
#include <stdlib.h>
#include "macro.h"

int main(int argc, const char *argv[]) {
    int i;
    
    if (argc <= 1) {
        fprintf(stderr, "No command line file name arguments provided.\n");
        return 1;
    }
    for (i = 1; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
        macroToTable(argv[i]);
    }

    return EXIT_SUCCESS;
}
