#include "str_helper.h"


char * crateJoinString(const char *str1, const char *str2) {
    size_t joinStrLen = strlen(str1) + strlen(str2) + 1;
    char *result = (char *)malloc(joinStrLen * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;  /* TODO - how to exit*/
    }
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

char * strdup(const char *str) {
    size_t strLen = strlen(str) + 1;
    char *duplicate = (char *)malloc(strLen * sizeof(char));
    if (duplicate == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
    } else {
        strcpy(duplicate, str);
    }
    return duplicate;
}


