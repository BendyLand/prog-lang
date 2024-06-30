#include "str.h" // stdio.h, stdlib.h, string.h, stdbool.h

void appendStr(string* original, char* suffix)
{
    size_t newLen = original->length + strlen(suffix) + 1;
    char* newData = (char*)realloc(original->data, newLen);
    if (!newData) {
        perror("Failed to reallocate memory for new string.");
        exit(EXIT_FAILURE);
    }
    strcat(newData, suffix);
    original->data = newData;
    original->length = newLen;
}

void freeStrArr(string** original)
{
    if (original) {
        size_t i = 0;
        while (original[i] != NULL) {
            freeStr(original[i]);
            i++;
        }
        free(original);
    }
}

string** splitStr(string* original, const char delim)
{
    string** result;
    size_t len = 0;
    for (size_t i = 0; i < original->length; i++)
        if (original->data[i] == delim)
            len++;
    result = (string**)malloc(sizeof(string*) * (len + 2));
    size_t n = 0;
    char* c = (char*)malloc(2);
    c[1] = '\0';
    string* temp = str("");
    for (size_t i = 0; i < original->length; i++) {
        if (original->data[i] == delim) {
            string* template = copyStr(temp);
            result[n] = template;
            clearStr(temp);
            n++;
        }
        c[0] = original->data[i];
        appendStr(temp, c);
    }
    if (strcmp(temp->data, "") != 0) {
        string* template = copyStr(temp);
        result[n] = template;
        n++;
    }
    result[n] = NULL;
    freeStr(temp);
    return result;
}

string* copyStr(string* original) 
{
    return str(original->data);
}

string* substr(string* original, size_t start, size_t end)
{
    size_t len = end - start;
    char* temp = (char*)malloc(len+1);
    strncpy(temp, original->data+start, len);
    temp[len] = '\0';
    string* result;
    result = str(temp);
    free(temp);
    return result;
}

bool isEmpty(string* str)
{
    if (str->length == 0 || strlen(str->data) < 1) {
        return true;
    }
    return false;
}

string* str(const char* text)
{
    string* result = (string*)malloc(sizeof(string));
    if (!result) {
        perror("Failed to allocate memory for string\n");
        exit(EXIT_FAILURE);
    }
    result->length = strlen(text);
    result->data = (char*)malloc(result->length + 1);
    if (!result->data) {
        perror("Failed to allocate memory for string data\n");
        free(result);
        exit(EXIT_FAILURE);
    }
    strcpy(result->data, text);
    return result;
}

void freeStr(string* str)
{
    if (str) {
        free(str->data);
        free(str);
    }
}

void clearStr(string* str)
{
    char* newData = (char*)realloc(str->data, 1);
    if (!newData) {
        perror("Failed to reallocate memory for cleared string.");
        exit(EXIT_FAILURE);
    }
    newData[0] = '\0';
    str->data = newData;
    str->length = 0;
}
