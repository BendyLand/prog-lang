#include "str.h" // stdio.h, stdlib.h, string.h, stdbool.h

string* readFile(char* path)
{
    FILE* ptr;
    char c;
    char buf[1024];
    ptr = fopen(path, "r");
    if (ptr == NULL) {
        printf("File can't be opened \n");
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
    return str(temp);
}

void lstrip(string* original)
{
    size_t len = original->length;
    size_t i = 0;
    while (original->data[i] == ' ' || original->data[i] == '\t') {
        i++;
    }
    char* temp = (char*)malloc(len - i + 1);
    size_t j = 0;
    while (i < len) {
        temp[j] = original->data[i];
        j++;
        i++;
    }
    clearStr(original);
    appendStr(original, temp);
    free(temp);
}

string* removeComments(string** arr)
{
    string* result = str("");
    size_t arrLen = 0;
    while (arr[arrLen] != NULL) arrLen++;
    for (size_t i = 0; i < arrLen; i++) {
        size_t idx = SIZE_MAX;
        // iterate through the line
        for (size_t j = 0; j < arr[i]->length; j++) {
            if (arr[i]->data[j] == '#') {
                idx = j;
                break;
            }
        }
        string* temp;
        if (idx != SIZE_MAX) {
            temp = substr(arr[i], 0, idx);
        }
        else {
            temp = copyStr(arr[i]);
        }
        appendStr(result, temp->data);
        appendStr(result, "\n");
        freeStr(temp);
    }
    return result;
}

// string* prepareFile(string* file)
// {
    // todo:
    // removeComments(file);
    // normalize(file);
    // removeEmptyLines(file);
    // return file;
// }