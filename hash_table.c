#include "hash_table.h"


/* TODO - make privet*/
unsigned int hashFunction(const char* key);
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
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);  /* TODO - How to exit*/
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


Entry *insertSymbolEntry(Entry *ht[TABLE_SIZE], const char *name, int property, int value) {
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
