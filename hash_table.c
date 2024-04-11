#include "hash_table.h"

/**
 * @brief Calculates the hash value for a given key using the hash function.
 *
 * This function calculates the hash value for a given key using the hash function.
 * The hash value is used to determine the index in the hash table where the key-value pair will be stored.
 *
 * @param key The key for which the hash value needs to be calculated.
 * @return The calculated hash value.
 */
unsigned int hashFunction(const char* key);


/**
 * Creates a new entry for a hash table.
 *
 * @param name The name of the entry.
 * @param property The property of the entry.
 * @param value The value of the entry.
 * @param data The data associated with the entry.
 * @return A pointer to the newly created entry, or NULL if memory allocation failed.
 */

Entry *createEntry(const char *name, int property, int value, const char *data);


unsigned int hashFunction(const char* key) {
    int i;
    unsigned int hash = 0;
     for (i = 0; i < strlen(key); i++) {
        hash = (hash * 31) + key[i];
    }
    return hash % TABLE_SIZE;
}


Entry *createEntry(const char *name, int property, int value, const char *data) {
    Entry *newEntry = (Entry *)malloc(sizeof(Entry));
    if (newEntry == NULL) {
        printf("Error: Memory allocation failed when created hash tavel entry.\n");
        return NULL;
    }
    newEntry->name = strdup(name);
    newEntry->property = property;
    newEntry->value = value;
    if (data != NULL) {
        newEntry->data = strdup(data);
    } else {
        newEntry->data = NULL;
    }
    newEntry->next = NULL;
    return newEntry;
}


Entry *insertEntry(Entry *ht[TABLE_SIZE], const char *name, Property property, int value, const char *data) {
    unsigned int index = hashFunction(name);
    Entry *newEntry = createEntry(name, property, value, data);

    if (ht[index] == NULL) {
        ht[index] = newEntry;
    } else {
        Entry *current = ht[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newEntry;
    }

    return newEntry;
}


Entry *insertSymbolEntExtEntry(Entry *ht[TABLE_SIZE], const char *name, int property, int value) {
    return insertEntry(ht, name, property, value, NULL);
}


Entry *getEntry(Entry *ht[TABLE_SIZE], const char *name) {
    unsigned int index = hashFunction(name);
    Entry *current = ht[index];

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}


void printTableEntries(Entry *ht[TABLE_SIZE]) {
    int i;
    Entry *current;
    for (i = 0; i < TABLE_SIZE; i++) {
        current = ht[i];
        while (current != NULL) {
            printf("Entry: %s, %d, %d,\n%s\n", current->name, current->property, current->value, current->data);
            current = current->next;
        }
    }
}


void freeTable(Entry *ht[TABLE_SIZE]) {
    int i;
    Entry *current = NULL;
    Entry *next = NULL;
    for (i = 0; i < TABLE_SIZE; i++) {
        current = ht[i];
        while (current != NULL) {
            next = current->next;
            free(current->name);
            free(current->data);
            free(current);
            current = next;
        }
    }
}
