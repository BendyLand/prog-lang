#include "keywords.h"
#include <stdio.h>
#include <string.h>

const char* keywords[] = {"if", "for", "let", "print", "puts"};
const int numKeywords = sizeof(keywords) / sizeof(char*);

int isKeyword(char* word) 
{
    for (int i = 0; i < numKeywords; i++) {
        int matchFound = strcmp(word, keywords[i]);
        if (matchFound) 
            return 1;
    }
    return 0;
}

const char* getKeyword(int index) 
{
    if (index >= 0 && index < numKeywords) 
        return keywords[index];
    return "";
}