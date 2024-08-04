#include <unistd.h>
#include "lexer.h"
#include "utils.h"
#include "token.h"

int main(int argc, char** argv)
{
    string* file;
    if (argc > 1) {
        file = readFile(argv[1]);
    }
    else {
        file = readFile("test.pr");
    }
    stringArray* lines = strArr(file, "\n");
    string* preppedFile = prepareFile(&lines);
    string* tempStr;
    for (size_t i = 0; i < lines->length; i++) {
        printf("Line: %s\n", lines->entries[i]->data);
        Token temp = parseLineToToken(lines->entries[i]);
        tempStr = tokenToStr(temp);
        printf("Token: %s\n", tempStr->data);
        strFree(tempStr);
    }
    strFree(file);
    strFree(preppedFile);
    strArrFree(lines);
    // sleep(10);
    return 0;
}
