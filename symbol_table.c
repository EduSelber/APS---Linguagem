#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

SymbolTable *symbol_table = NULL;  // Initialize as NULL pointer

void symbol_table_init(SymbolTable **table) {
    *table = malloc(sizeof(SymbolTable));
    (*table)->entries = NULL;
}

void symbol_table_destroy(SymbolTable *table) {
    if (!table) return;
    
    SymbolTableEntry *entry = table->entries;
    while (entry != NULL) {
        SymbolTableEntry *next = entry->next;
        free(entry->name);
        free(entry);
        entry = next;
    }
    free(table);
}

double symbol_table_get(SymbolTable *table, const char *name) {
    if (!table) return 0.0;
    
    SymbolTableEntry *entry = table->entries;
    while (entry != NULL) {
        if (strcmp(entry->name, name) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return 0.0;
}

void symbol_table_set(SymbolTable *table, const char *name, double value) {
    if (!table) return;
    
    SymbolTableEntry *entry = table->entries;
    while (entry != NULL) {
        if (strcmp(entry->name, name) == 0) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }

    SymbolTableEntry *new_entry = malloc(sizeof(SymbolTableEntry));
    new_entry->name = strdup(name);
    new_entry->value = value;
    new_entry->next = table->entries;
    table->entries = new_entry;
}