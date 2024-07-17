#ifndef LEXER_H
#define LEXER_H

#include "str.h" // stdio.h, stdlib.h, string.h 
#include "utils.h"

string* removeComments(stringArray* arr);
string* normalize(stringArray* arr);
string* removeEmptyLines(stringArray* arr);
string* prepareFile(stringArray* arr);

#endif