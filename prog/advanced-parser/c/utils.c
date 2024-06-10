#include "utils.h"

void splitIntoLines(char** buf, char* file)
{
    size_t len = strlen(file);
    char* strCopy = (char*)malloc(len+1);
    strcpy(strCopy, file);

    size_t count = 0;
    char* token = strtok(strCopy, "\n");
    while (token != NULL) {
        token = strtok(NULL, "\n");
        count++;
    }
    rewind(token);
    char** result = (char**)malloc(sizeof(char*) * count);
    size_t i = 0;
    while (token != NULL) {
        size_t lineLen = strlen(token);
        // result[i] = (char*)malloc(lineLen+1);
        // result = token;
        // strtok(NULL, "\n");
    }
    free(strCopy);
    return result;
}