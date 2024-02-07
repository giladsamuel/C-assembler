#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_helper.h"

#define TABLE_SIZE 104

/*#define INITIAL_TABLE_SIZE 104*/ /* TODO - hash table can grow*/
#define TABLE_SIZE 104
typedef struct Entry {
    char* name;
    int address;
    char* data;
    struct Entry *next;
} Entry;


Entry *insertEntry(Entry *ht[TABLE_SIZE], const char *name, int address, const char *data);
Entry *getEntry(Entry *ht[TABLE_SIZE], const char *name);
void printTableEntries(Entry *ht[TABLE_SIZE]);
/*void freeTable(Entry *ht[TABLE_SIZE]);  TODO - free table*/
#endif
