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

typedef struct
{
	Token token;
	string* line;
} TokenLine;

Token parseLineToToken(string* line);
string* tokenToStr(Token token);
TokenLine* saveTokenLine(Token token, string* line);
void tokenLineFree(TokenLine* line);