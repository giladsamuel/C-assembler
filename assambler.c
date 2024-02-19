#include <stdio.h>
#include <stdlib.h>
#include "str_helper.h"
#include "preprocessor.h"
#include "first_pass.h"

/**TODO list:
 *          1.header including 
 *          2. change error messages
 *          3. memory allocation exit handle 
 *          4. make privet functions
 *          5. error handling
 *          6. change error printing to stdout instead of stderr
 *          7. mange memory, free all memory allocation
 *          8. change all error messages to be more informative
 *          9. check that constant or label is not a reserved word
 *          10.use switch 
 *          11.second pass check that all labels are defined
 *          12. print the whole line in case of error
 */ 

int main(int argc, const char *argv[]) {
    int i;
    
    if (argc <= 1) {
        printf("No command line file name arguments provided.\n");
        return 1;
    }
    for (i = 1; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
        if (preprocessMacros(argv[i]) != 0) {
            printf("Error: Failed to convert macro file to table.\n"); /* TODO - change error*/
            return EXIT_FAILURE;
        }
        if (firstPass(argv[i]) == -1) {
            printf("Errors in compiler's first pass.\n");
            
        }
        /*if (secondPass(argv[i]) == -1) {
            printf("Errors in compiler's second pass.\n");
        }*/
    }

    return EXIT_SUCCESS;
}
