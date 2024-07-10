#include "str.h" // stdio.h, stdlib.h, string.h

string* str(const char* text)
{
    if (!text) {
        perror("Null pointer passed to str().\n");
        exit(EXIT_FAILURE);
    }
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
    result->data[length] = '\0';
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
    string* result;
    if (original->length > 0) {
        char* temp = strdup(original->data);
        result = str(temp);
        free(temp);
    }
    else {
        result = str("");
    }
    return result;
}

stringArray* strSplit(string* original, char* delim)
{
    string* copy = strCopy(original);
    string* copy2 = strCopy(original);
    stringArray* result = (stringArray*)malloc(sizeof(stringArray));
    size_t i = 0;
    char* token = strtok(copy->data, delim);
    while (token != NULL) {
        i++;
        token = strtok(NULL, delim);
    }
    free(token);
    token = strtok(copy2->data, delim);
    result->entries = (string**)malloc(sizeof(string*) * (i+1));
    size_t j = 0; 
    while (token != NULL) {
        string* temp = str(token);
        result->entries[j] = temp;
        j++;
        token = strtok(NULL, delim);
    }
    result->entries[j] = NULL;
    result->length = i;
    strFree(copy);
    strFree(copy2);
    return result;
}

void strArrFree(stringArray* arr)
{
    if (arr) {
        if (arr->entries && arr->length > 0) {
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

bool strIsEmpty(string* str)
{
    return (strcmp(str->data, "") == 0) || str->length == 0;
}

string* substr(string* original, size_t start, size_t end)
{
    size_t newLen = (end - start);
    char* temp = (char*)malloc(newLen + 1);
    size_t n = 0;
    for (size_t i = start; i < end; i++) {
        temp[n] = original->data[i];
        n++;
    }
    temp[n] = '\0';
    string* result = str(temp);
    free(temp);
    return result;
}

void strArrDisplay(stringArray* arr)
{
    for (size_t i = 0; i < arr->length; i++) {
        puts(arr->entries[i]->data);
    }
}

bool strContains(string* str, const char c)
{
    for (size_t i = 0; i < str->length; i++) {
        if (str->data[i] == c) return true;
    }
    return false;
}