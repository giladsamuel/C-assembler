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


int isValidName(Entry *hashTable[], const char *name) {
    int i;
    if (name == NULL) {
        return 0;
    }
    if (strlen(name) > 31) {
        fprintf(stderr, "\nError: Name %s is too long.\n", name);
        return 0;
    }
    if (!isalpha(name[0])) {
        fprintf(stderr, "\nError: Name %s must start with a letter.\n", name);
        return 0;
    }
    for (i = 1; i < strlen(name); i++) {
        if (!isalnum(name[i])) {
            fprintf(stderr, "\nError: Name %s must contain only letters and digits.\n", name);
            return 0;
        }
    }
    if (getEntry(hashTable, name) != NULL) {
        fprintf(stderr, "\nError: '%s' is already defined as constant or label.\n", name);
        return 0;
    }

    return 1;
}


int isValidValue(const char *value) {
    int i;
    if (value == NULL) {
        return 0;
    }
    if (value[0] == '-' || value[0] == '+') {
        i = 1;
    } else {
        i = 0;
    }
    for (; i < strlen(value); i++) {
        if (!isdigit(value[i])) {
            printf("\nError: Value %s must contain only digits.\n", value);
            return 0;
        }
    }
    return 1;
}