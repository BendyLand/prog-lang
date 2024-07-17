#include <unistd.h>
#include "lexer.h" // "str.h", "utils.h", stdio.h, stdlib.h, string.h

int main(void)
{
    string* file = readFile("../../../test.pr");
    puts(file->data);
    stringArray* lines = strSplit(file, "\n");
    string* preparedFile = prepareFile(lines);
    puts(preparedFile->data);
    strFree(preparedFile);
    puts("Run leaks now...");
    sleep(10);
    return 0;
}

void comment_storage()
{
    // gcc main.c str.c utils.c lexer.c -o main -fsanitize=address -g
    // todo: design data type storage
    // todo: design control flow 
    // todo: execute top level print statements
}
