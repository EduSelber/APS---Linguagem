#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int r, g, b;
} Color;

typedef struct Shape {
    int type;
    union {
        struct { double x, y, radius; } circle;
        struct { double x, y, width, height; } rect;
        struct { double x1, y1, x2, y2; } line;
    } data;
    Color color;
    struct Shape *next;
} Shape;

typedef struct Group {
    double x_offset, y_offset;
    struct Shape *shapes;
    struct Group *parent;
} Group;

typedef struct SymbolTableEntry {
    char *name;
    double value;
    struct SymbolTableEntry *next;
} SymbolTableEntry;

typedef struct {
    SymbolTableEntry *entries;
} SymbolTable;

extern SymbolTable *symbol_table;  // Changed to pointer

void symbol_table_init(SymbolTable **table);  // Changed to pointer-to-pointer
void symbol_table_destroy(SymbolTable *table);
double symbol_table_get(SymbolTable *table, const char *name);
void symbol_table_set(SymbolTable *table, const char *name, double value);

#endif