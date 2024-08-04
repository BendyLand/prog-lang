#include "utils.h"
#include "str.h" // stdio.h, stdlib.h, string.h, stdbool.h

string* readFile(char* path)
{
    FILE* ptr;
    char c;
    char buf[10000];
    ptr = fopen(path, "r");
    if (ptr == NULL) {
        printf("File can't be opened.\n");
        exit(EXIT_FAILURE);
    }
    size_t current = 0;
    do {
        c = fgetc(ptr);
        buf[current] = c;
        current++;
    } while (c != EOF);
    fclose(ptr);
    char* temp = (char*)malloc(current); // `current` is already 1 past where we want
    for (size_t i = 0; i < current-1; i++) {
        temp[i] = buf[i];
    }
    temp[current-1] = '\0';
    string* result = str(temp);
    free(temp);
    return result;
}

void lstrip(string* original)
{
    size_t len = original->length;
    size_t i = 0;
    while (original->data[i] == ' ' || original->data[i] == '\t') i++;
    char* temp = (char*)malloc(len - i + 1);
    size_t j = 0;
    while (i < len) {
        temp[j] = original->data[i];
        j++;
        i++;
    }
    temp[j] = '\0';
    strClear(original);
    strAppend(original, temp);
    free(temp);
}
