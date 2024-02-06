#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

/*#define INITIAL_TABLE_SIZE 104*/ /* TODO - hash table can grow*/
#define TABLE_SIZE 104
typedef struct MacroEntry {
    char* mcrName;
    char* mcrAddress;
    char* mcrData;
    struct MacroEntry* next;
} MacroEntry;

MacroEntry *hashTable[TABLE_SIZE] = {NULL};


unsigned int hashFunction(const char* key) {
    int i;
    unsigned int hash = 0;
    for (i = 0; i < strlen(key); i++) {
        hash = (hash * 31) + key[i];
    }
    return hash % TABLE_SIZE;
}

MacroEntry* createMacroEntry(const char* key, const char* value) {
    MacroEntry* newMacroEntry = (MacroEntry*)malloc(sizeof(MacroEntry));
    newMacroEntry->key = strdup(key);
    newMacroEntry->value = strdup(value);
    newMacroEntry->next = NULL;
    return newMacroEntry;
}

void insert(HashTable* ht, const char* key, const char* value) {
    unsigned int index = hash(key);
    Node* newNode = createNode(key, value);

    if (ht->table[index] == NULL) {
        ht->table[index] = newNode;
    } else {
        Node* current = ht->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

const char* get(HashTable* ht, const char* key) {
    unsigned int index = hash(key);
    Node* current = ht->table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

int main() {
    HashTable ht;
    memset(&ht, 0, sizeof(HashTable));

    // Example usage
    insert(&ht, "MACRO1", "Value1");
    insert(&ht, "MACRO2", "Value2");

    const char* value1 = get(&ht, "MACRO1");
    const char* value2 = get(&ht, "MACRO2");

    printf("Value1: %s\n", value1);
    printf("Value2: %s\n", value2);

    return 0;
}
