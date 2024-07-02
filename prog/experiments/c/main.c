#include "lexer.h" // "str.h", "utils.h", stdio.h, stdlib.h, string.h

int main(void)
{
    string* fileContents = readFile("../../../test.pr");
    string** strArr = strSplit(fileContents, '\n');
    strFree(fileContents);

    string* noComments = removeComments(strArr);
    strArrFree(strArr);

    string** newStrArr = strSplit(noComments, '\n');
    string* normalizedStr = normalize(newStrArr);

    string** thirdStrArr = strSplit(normalizedStr, '\n');
    strFree(normalizedStr);
    string* noEmptyLines = removeEmptyLines(thirdStrArr);
    strArrFree(thirdStrArr);

    puts(noEmptyLines->data);

    strArrFree(newStrArr);
    strFree(noEmptyLines);

    //todo: create prepareFile(string* file);

    return 0;
}

