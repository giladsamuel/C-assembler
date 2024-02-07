#include <stdio.h>
#include <stdlib.h>
#include "preprocessor.h"

int main(int argc, const char *argv[]) {
    int i;
    
    if (argc <= 1) {
        fprintf(stderr, "No command line file name arguments provided.\n");
        return 1;
    }
    for (i = 1; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
        if (preprocessMacros(argv[i]) != 0) {
            fprintf(stderr, "Error: Failed to convert macro file to table.\n"); /* TODO - change error*/
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
