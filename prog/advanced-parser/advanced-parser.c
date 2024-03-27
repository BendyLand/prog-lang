#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "keywords.h"
#include "lexer.h"

#define MAX_LINES 100

int main(void) {
    char* data = getFileContents();
    char** lines = (char**)malloc(sizeof(char*) * (MAX_LINES + 1));
    memset(lines, 0, sizeof(char*) * (MAX_LINES + 1));

    int numLines = splitIntoLines(lines, data);
    char** lineTokens = (char**)malloc(sizeof(char*) * MAX_LINES + 1);
    removeComments(lines);

    int i = 0;
    while (lines[i] != NULL) {
        // puts(lines[i]);
        tokenizeLine(lineTokens, lines[i]);
        int j = 0;
        while (lineTokens[j] != NULL) {
            trimLeadingWhitespace(lineTokens[j]);
            printf("%s\n", lineTokens[j]);
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
