// #include "lexer.h" // "str.h", "utils.h", stdio.h, stdlib.h, string.h

#include <unistd.h>
#include "str.h"
#include "utils.h"

int main(void)
{
    string* test = str("The quick brown fox jumps over the lazy dog");
    puts(test->data);
    printf("Length: %zu\n", test->length);

    strAppend(test, ". And his owner's name was Ben!");
    puts(test->data);
    printf("Length: %zu\n", test->length);

    stringArray* testArr = strSplit(test, ' ');
    printf("Arr length: %zu\n", testArr->length);

    strFree(test);
    strArrFree(testArr);

    // gcc main.c str.c utils.c -o main -fsanitize=address -g
    // sleep(20);

    return 0;
}

void comment_storage()
{
    // comment storage:
    // todo: design data type storage
    // todo: design control flow 
    // todo: execute top level print statements
    // string* fileContents = readFile("../../../test.pr");
    // string** strArr = strSplit(fileContents, '\n');
    // string* preparedFile = prepareFile(strArr);
    // string** newStrArr = strSplit(preparedFile, '\n');
}
