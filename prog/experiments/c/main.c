#include "lexer.h" // "str.h", "utils.h", stdio.h, stdlib.h, string.h

int main(void)
{
    string* fileContents = readFile("../../../test.pr");
    string** strArr = strSplit(fileContents, '\n');
    strFree(fileContents);
    string* preparedFile = prepareFile(strArr);
    puts(preparedFile->data);
    strArrFree(strArr);
    strFree(preparedFile);
    // puts("Run leaks now...");
    // fscanf(stdin, "c");
    return 0;
}


