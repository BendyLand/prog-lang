#pragma once

#include <stdio.h>
#include <glib.h>
#include "str.h"
#include "scope.h"
#include "types.h"

typedef struct
{
    string* name;
    Type type;
    bool isMut;
} Symbol;

typedef struct
{
    size_t id;
    Scope scope;
    GHashTable* symbols;
} SymbolTable;


