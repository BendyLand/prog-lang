#include "lexer.h"

string* prepareFile(stringArray* arr)
{
    string* noComments = removeComments(arr);
    strArrFree(arr);
    arr = strSplit(noComments, "\n");
    strFree(noComments);
    string* normalizedStr = normalize(arr);
    strArrFree(arr);
    arr = strSplit(normalizedStr, "\n");
    string* noEmptyLines = removeEmptyLines(arr);
    strFree(normalizedStr);
    return noEmptyLines;
}

string* removeEmptyLines(stringArray* arr)
{
    string* result = str("");
    for (size_t i = 0; i < arr->length; i++) {
        if (!strIsEmpty(arr->entries[i])) {
            strAppend(result, arr->entries[i]->data);
            strAppend(result, "\n");
        }
    }
    return result;
}

string* normalize(stringArray* arr)
{
    string* result = str("");
    for (size_t i = 0; i < arr->length; i++) {
        string* temp = strCopy(arr->entries[i]);
        lstrip(temp);
        strAppend(result, temp->data);
        strAppend(result, "\n");
        strFree(temp);
    }
    return result;
}

string* removeComments(stringArray* lines)
{
    string* result = str("");
    for (size_t i = 0; i < lines->length; i++) {
        string* current = lines->entries[i];
        char* temp = (char*)malloc(current->length + 1);
        for (size_t j = 0; j < current->length; j++) {
            if (current->data[j] == '#') {
                temp[j] = '\0';
                goto Next;
            }
            temp[j] = current->data[j];
        }
        temp[current->length] = '\0';
        Next:
        strAppend(result, temp);
        strAppend(result, "\n");
        free(temp);
    }
    return result;
}
