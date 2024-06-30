#include "str.h" // stdio.h, stdlib.h, string.h
#include "utils.h"

int main(void)
{
    string* fileContents = readFile("../../../test.pr");

    string** strArr = splitStr(fileContents, '\n');

    string* noComments = removeComments(strArr);
    puts(noComments->data);

    //todo: create prepareFile(string* file);

    freeStr(fileContents);
    freeStrArr(strArr);

    return 0;
}

// string* prepareFile(string* file)
// {
     // removeComments(file);
     // normalize(file);
     // removeEmptyLines(file);
     // return file;
// }
