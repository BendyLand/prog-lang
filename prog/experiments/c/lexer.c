#include "lexer.h"

// string* prepareFile(string* file)
// {
     // removeComments(file);
     // normalize(file);
     // removeEmptyLines(file);
     // return file;
// }

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
