#ifndef DIRECTIVES_H
#define DIRECTIVES_H

#include "hash_table.h"


typedef enum Directive{
    DATA,
    STRING,
    ENTRY,
    EXTERN
} DirectiveType;


DirectiveType identifyDirectiveType(char *directive);
int parseValidateDirective(Entry *symbolHashTable[], char *sentence, DirectiveType directiveType, int lineNumber);
int parseValidateDataDirective(Entry *symbolHashTable[], char *sentence, int lineNumber);
int parseValidateStringDirective(char *sentence, int lineNumber);
int parseValidateInsertEntryExternDirective(Entry *symbolHashTable[], char *sentence, int lineNumber, Property property);

#endif