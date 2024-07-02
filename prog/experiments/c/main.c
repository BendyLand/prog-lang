#include "lexer.h" // "str.h", "utils.h", stdio.h, stdlib.h, string.h

int main(void)
{
    string* fileContents = readFile("../../../test.pr");
    string** strArr = strSplit(fileContents, '\n');
    string* noComments = removeComments(strArr);
    string** newStrArr = strSplit(noComments, '\n');
    string* normalizedStr = normalize(newStrArr);

    puts(normalizedStr->data);

    //todo: create prepareFile(string* file);

    strFree(fileContents);
    strFree(normalizedStr);
    strArrFree(strArr);
    strArrFree(newStrArr);

    return 0;
}

