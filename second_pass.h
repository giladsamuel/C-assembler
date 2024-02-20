#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include <stdio.h>
#include "hash_table.h"

int secondPass(const char* fileName, FILE *amFile, Entry *symbolHashTable[], int errFlag);

#endif