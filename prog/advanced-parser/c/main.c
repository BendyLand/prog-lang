#include "lexer.h"
#include "utils.h" 

const size_t MAX_LINES = 100;

int main(void)
{
    char* data = getFileContents();
    char** lines = (char**)malloc(sizeof(char*) * (MAX_LINES + 1));
    memset(lines, 0, sizeof(char*) * (MAX_LINES + 1));

    int numLines = splitIntoLines(lines, data);
    char** lineTokens = (char**)malloc(sizeof(char*) * MAX_LINES + 1);

    size_t i = 0;
    while (lines[i] != NULL) {
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
