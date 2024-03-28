#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "keywords.h"
#include "lexer.h"

#define MAX_LINES 100

void serveKeywordToken(char**);

int main(void) {
    char* data = getFileContents();
    char** lines = (char**)malloc(sizeof(char*) * (MAX_LINES + 1));
    memset(lines, 0, sizeof(char*) * (MAX_LINES + 1));

    int numLines = splitIntoLines(lines, data);
    char** lineTokens = (char**)malloc(sizeof(char*) * MAX_LINES + 1);
    removeComments(lines);

    int i = 0;
    while (lines[i] != NULL) {
        trimLeadingWhitespace(lines[i]);
        tokenizeLine(lineTokens, lines[i]);
        serveKeywordToken(lineTokens);
        puts("");
        int j = 0;
        while (lineTokens[j] != NULL) {
            // printf("%d\n", j);
            // printf("%s\n", lineTokens[j]);
            if (strcmp(lineTokens[j], "") != 0)
                free(lineTokens[j]);
            j++;
        }
        free(lines[i]);
        i++;
    }
    free(lines);
    free(lineTokens);
    free(data);
    // fscanf(stdin, "c");

    return 0;
}

void serveKeywordToken(char** tokens) {
    if (strcmp(tokens[0], "print") == 0) 
        printf("%s", tokens[1]);
    else if (strcmp(tokens[0], "puts") == 0) 
        printf("%s\n", tokens[1]);
    else if (strcmp(tokens[0], "let") == 0) 
        puts("I'm in the `let` branch");
    else if (strcmp(tokens[0], "if") == 0) 
        puts("I'm in the `if` branch");
    else if (strcmp(tokens[0], "for") == 0) 
        puts("I'm in the `for` branch");
    else 
        puts("This line doesn't contain a keyword");
    
}