#pragma once

#include <stdio.h>
#include "str.h"

typedef enum 
{
    LET,
    PRINT,
    PUTS,
    IF,
    ELIF,
    ELSE,
    FOR,
    C_BRACE,
    O_BRACE,
    NA
} Token;

Token parseLineToToken(string* line);
string* tokenToStr(Token token);
