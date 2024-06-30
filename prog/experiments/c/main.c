#include "lexer.h" // "str.h", "utils.h", stdio.h, stdlib.h, string.h

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

