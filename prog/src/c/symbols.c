#include "symbols.h"

SymbolTable* newSymbolTable(Scope scope, size_t id)
{
    SymbolTable* table = (SymbolTable*)malloc(sizeof(SymbolTable));
    table->id = id;
    table->scope = scope;
    table->symbols = g_hash_table_new(g_direct_hash, g_direct_equal);
    return table;
}