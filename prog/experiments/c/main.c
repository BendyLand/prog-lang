#include <unistd.h>
#include "lexer.h" // "str.h", "utils.h", stdio.h, stdlib.h, string.h

int main(void)
{
    string* file = readFile("../../../test.pr");
    stringArray* lines = strSplit(file, "\n");
    string* preparedFile = prepareFile(lines);
    puts(preparedFile->data);
    strFree(preparedFile);
    sleep(10);
    return 0;
}

void comment_storage()
{
    // gcc main.c str.c utils.c -o main -fsanitize=address -g
    // comment storage:
    // todo: design data type storage
    // todo: design control flow 
    // todo: execute top level print statements
}
