#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_helper.h"

#define TABLE_SIZE 104
#define MEMORY_OFFSET 100

typedef enum PropertyType{
    NO_PROPERTY,
    MDEFINE,
    CODE,
    DATA_STRING,
    ENTRANCE,
    EXTERNAL
} Property;

typedef struct Entry {
    char *name;
    Property property;
    int value;
    char *data;
    struct Entry *next;
} Entry;



/**
 * Inserts a new entry into the hash table.
 *
 * @param ht The hash table array.
 * @param name The name of the entry.
 * @param property The property of the entry.
 * @param value The value of the entry.
 * @param data The data of the entry.
 * @return The newly inserted entry.
 */
Entry *insertEntry(Entry *ht[TABLE_SIZE], const char *name, Property property, int value, const char *data);


/**
 * Inserts a symbol entry into the hash table.
 *
 * @param ht The hash table.
 * @param name The name of the symbol.
 * @param property The property of the symbol.
 * @param value The value of the symbol.
 * @return The inserted symbol entry.
 */
Entry *insertSymbolEntExtEntry(Entry *ht[TABLE_SIZE], const char *name, int property, int value);

/**
 * Retrieves the entry with the specified name from the hash table.
 *
 * @param ht The hash table array.
 * @param name The name of the entry to be retrieved.
 * @return The entry with the specified name.
 */
Entry *getEntry(Entry *ht[TABLE_SIZE], const char *name);


/**
 * Prints all the entries in the hash table.
 *
 * @param ht The hash table array.
 */
void printTableEntries(Entry *ht[TABLE_SIZE]);


/**
 * Frees the memory allocated for the hash table.
 * 
 * @param ht The hash table to be freed.
 */
void freeTable(Entry *ht[TABLE_SIZE]);

#endif
