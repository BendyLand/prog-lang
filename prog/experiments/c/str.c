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
    perror("Error: null pointer passed to strClear.\n");
    exit(EXIT_FAILURE);
}

string* strCopy(string* original)
{
    if (!original) {
        perror("Error: null pointer passed to strCopy.\n");
        exit(EXIT_FAILURE);
    }
    char* temp = strdup(original->data);
    string* result = str(temp);
    free(temp);
    return result;
}

stringArray* strSplit(string* original, const char delim)
{
    string* copy = strCopy(original);
    if (!copy) {
        perror("Unable to copy original string.\n");
        exit(EXIT_FAILURE);
    }
    stringArray* result = (stringArray*)malloc(sizeof(stringArray));
    if (!result) {
        perror("Error: Unable to allocate memory for stringArray struct.\n");
        strFree(copy);
        exit(EXIT_FAILURE);
    }
    size_t len = 1; // at least 1 token
    for (size_t i = 0; i < copy->length; i++) {
        if (copy->data[i] == delim) len++;
    }
    result->entries = (string**)malloc(sizeof(string*) * (len + 1));
    if (!result->entries) {
        perror("Error: Unable to allocate memory for string array.\n");
        strFree(copy);
        free(result);
        exit(EXIT_FAILURE);
    }
    char* token = strtok(copy->data, &delim);
    size_t i = 0;
    while (token != NULL) {
        result->entries[i] = str(token);
        if (!result->entries[i]) {
            for (size_t j = 0; j < i; j++) {
                strFree(result->entries[j]);
            }
            free(result->entries);
            free(result);
            strFree(copy);
            perror("Error: Unable to create string from token.\n");
            exit(EXIT_FAILURE);
        }
        i++;
        token = strtok(NULL, &delim);
    }
    strFree(copy);
    result->entries[len] = NULL;
    result->length = len;
    return result;
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