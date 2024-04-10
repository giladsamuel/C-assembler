#include <stdio.h>
#include <stdlib.h>
#include "str_helper.h"
#include "preprocessor.h"
#include "first_pass.h"


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
