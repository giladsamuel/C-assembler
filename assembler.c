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
 *          13. maybe .am file can pass from the preprocessor to first pass
 *          14. change makefile recipe to use all .h files for each trans-unit
 *          15. move insertMacro to hashTable to hashTable files.
 */ 

int main(int argc, const char *argv[]) {
    int i;
    int errFlag = 0;
    
    if (argc <= 1) {
        printf("No command line file name arguments provided.\n");
        return 1;
    }
    for (i = 1; i < argc; i++) {
        errFlag = 0;

        printf("Argument %d: %s\n", i, argv[i]);
        if (NOT preprocessMacros(argv[i])) {
            printf("Error: Fail in macro preprocessor.\n");
            continue;
        }
        errFlag = firstPass(argv[i]);
        if (errFlag) {
            printf("Errors in compiler's first and second passes.\n");
        }
    }

    return EXIT_SUCCESS;
}
