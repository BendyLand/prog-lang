#include "lexer.h"

// string* prepareFile(string* file)
// {
     // removeComments(file);
     // normalize(file);
     // removeEmptyLines(file);
     // return file;
// }

string* removeEmptyLines(string** arr) 
{
    string* result = str("");
    size_t arrLen = strArrLen(arr);
    for (size_t i = 0; i < arrLen; i++) {
        if (!strIsEmpty(arr[i])) {
            strAppend(result, arr[i]->data);
            strAppend(result, "\n");
        }
    }
    return result;
}

string* normalize(string** arr)
{
    string* result = str("");
    size_t arrLen = strArrLen(arr);
    for (size_t i = 0; i < arrLen; i++) {
        string* temp = strCopy(arr[i]);
        lstrip(temp);
        strAppend(result, temp->data);
        strAppend(result, "\n");
        strFree(temp);
    }
    return result;
}

string* removeComments(string** arr)
{
    string* result = str("");
    size_t arrLen = strArrLen(arr);
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
            temp = strCopy(arr[i]);
        }
        strAppend(result, temp->data);
        strAppend(result, "\n");
        strFree(temp);
    }
    return result;
}
