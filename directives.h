#ifndef DIRECTIVES_H
#define DIRECTIVES_H

#include "hash_table.h"
#include "first_pass.h"
#include "binary_word.h"

typedef enum Directive{
    DATA,
    STRING,
    ENTRY,
    EXTERN
} DirectiveType;


DirectiveType identifyDirectiveType(const char *directive);
int parseValidateDirective(Entry *symbolHashTable[], Entry *entExtHashTable[], char *sentence, DirectiveType directiveType, int lineNumber, int dataCounter, char *dataWordsArray[]);
int parseValidateDataDirective(Entry *symbolHashTable[], char *sentence, int lineNumber, int dataCounter, char *dataWordsArray[]);
int parseValidateStringDirective(char *sentence, int lineNumber, int dataCounter, char *dataWordsArray[]);
int parseValidateInsertEntryExternDirective(Entry *symbolHashTable[], Entry *entExtHashTable[], char *sentence, int lineNumber, Property property);

#endif