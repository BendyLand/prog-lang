#include "str.h" // stdio.h, stdlib.h, string.h
#include "utils.h"

string* readFile(char* path);

int main(void)
{
    string* fileContents = readFile("../../../test.pr");
    puts(fileContents->data);
    freeStr(fileContents);

    return 0;
}
