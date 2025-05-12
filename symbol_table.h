#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int r, g, b;
} Color;

typedef struct SymbolTableEntry {
    char *name;
    double value;
    struct SymbolTableEntry *next;
} SymbolTableEntry;

typedef struct SymbolTable {
    SymbolTableEntry *entries;
} SymbolTable;

extern SymbolTable *symbol_table;

// Symbol table functions
void symbol_table_init(SymbolTable **table);
void symbol_table_destroy(SymbolTable *table);
double symbol_table_get(SymbolTable *table, const char *name);
void symbol_table_set(SymbolTable *table, const char *name, double value);

#endif