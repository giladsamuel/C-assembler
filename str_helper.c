#include "str_helper.h"


char * crateJoinString(const char *str1, const char *str2) {
    size_t joinStrLen = strlen(str1) + strlen(str2) + 1;
    char *result = (char *)malloc(joinStrLen * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}