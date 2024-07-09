// #include "lexer.h" // "str.h", "utils.h", stdio.h, stdlib.h, string.h
#include "utils.h"
#include "str.h"

int main(void)
{
    string* test = str("The quick brown fox jumps over the lazy dog");
    puts(test->data);
    printf("Length: %zu\n", test->length);

    strAppend(test, ". And his owner's name was Ben!");
    puts(test->data);
    printf("Length: %zu\n", test->length);

    // stringArray* testArr = strSplit(test, ' ');
    // for (size_t i = 0; i < testArr->length; i++) {
    //     printf("Line: %s\n", testArr->entries[i]->data);
    // }
    // printf("Arr length: %zu\n", testArr->length);

    strFree(test);
    // strArrFree(testArr);
    // printf("Arr length: %zu\n", testArr->length);

    // string* fileContents = readFile("../../../test.pr");
    // string** strArr = strSplit(fileContents, '\n');
    // string* preparedFile = prepareFile(strArr);
    // string** newStrArr = strSplit(preparedFile, '\n');


    return 0;
}

void comment_storage()
{
    // comment storage:
    // todo: design data type storage
    // todo: design control flow 
    // todo: execute top level print statements


}