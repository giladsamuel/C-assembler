#include <stdio.h>
#include <stdlib.h>
#include "preprocessor.h"
#include "first_pass.h"

/**TODO list:
 *          1.header including 
 *          2. change error messages
 *          3. memory allocation exit handle 
 *          4. make privet functions
 *          5. error handling
 *          6. change error printing to stdout instead of stderr
 * 
 */ 

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
        /*if (firstPass(argv[i]) != 0) {
            fprintf(stderr, "Error: Failed to convert macro file to table.\n");  TODO - change error
            return EXIT_FAILURE;
        }*/
    }

    return EXIT_SUCCESS;
}
