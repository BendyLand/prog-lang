#include "str.h" // stdio.h, stdlib.h, string.h

string* str(const char* text)
{
    size_t length = strlen(text);
    string* result = (string*)malloc(sizeof(string));
    if (!result) {
        perror("Problem allocating memory for string struct.\n");
        exit(EXIT_FAILURE);
    }
    result->data = (char*)malloc(length + 1);
    if (!result->data) {
        perror("Problem allocating memory for string data.\n");
        free(result);
        exit(EXIT_FAILURE);
    }
    result->length = length;
    strcpy(result->data, text);
    return result;
}

void strFree(string* str)
{
    if (str) {
        if (str->data) {
            free(str->data);
            str->data = NULL;
        }
        free(str);
        str = NULL;
        return;
    }
    perror("Problem freeing string.\n");
    exit(EXIT_FAILURE);
}

void strAppend(string* original, const char* suffix)
{
    size_t newLen = original->length + strlen(suffix);
    char* temp = (char*)realloc(original->data, newLen + 1);
    if (!temp) {
        perror("Failed to reallocate memory for new string.\n");
        exit(EXIT_FAILURE);
    }
    strcat(temp, suffix);
    original->data = temp;
    original->length = newLen;
}

void strClear(string* original)
{
    if (original && original->data) {
        free(original->data);
        original->data = (char*)malloc(1);
        if (!original->data) {
            perror("Failed to allocate memory for cleared string.\n");
            exit(EXIT_FAILURE);
        }
        original->data[0] = '\0';
        original->length = 0;
        return;
    }
    perror("strClear: null pointer passed.\n");
    exit(EXIT_FAILURE);
}

stringArray* strSplit(string* original, const char delim)
{
    
}

void strArrFree(stringArray* arr)
{
    if (arr) {
        if (arr->entries) {
            for (size_t i = 0; i < arr->length; i++) {
                if (arr->entries[i]->data) {
                    free(arr->entries[i]->data);
                    arr->entries[i]->data = NULL;
                }
                free(arr->entries[i]);
                arr->entries[i] = NULL;
            }
            free(arr->entries);
            arr->entries = NULL;
        }
        free(arr);
        arr = NULL;
        return;
    }
    perror("Error: string array doesn't exist.\n");
    exit(EXIT_FAILURE);
}