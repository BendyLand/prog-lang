#ifndef LEXER_H
#define LEXER_H

#include "str.h" // stdio.h, stdlib.h, string.h 
#include "utils.h"

string* removeComments(string** arr);
string* normalize(string** arr);

#endif