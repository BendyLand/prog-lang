#include "str.h" // stdio.h, stdlib.h, string.h
#include "utils.h"

int main(void)
{
    string* fileContents = readFile("../../../test.pr");
    // puts(fileContents->data);

    string** strArr = splitStr(fileContents, '\n');

    int i = 0;
    while (strArr[i] != NULL) {
        puts(strArr[i]->data);
        i++;
        if (i > 100) break;
    }

    //todo: create prepareFile(string* file);

    freeStr(fileContents);
    freeStrArr(strArr);
    return 0;
}

// string* prepareFile(string* file)
// {
//     // todo:
//     // removeComments(file);
//     // normalize(file);
//     // removeEmptyLines(file);
//     // return file;
// }
