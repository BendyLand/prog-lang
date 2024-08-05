#include <unistd.h>
#include "lexer.h"
#include "token.h"
#include "utils.h"

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
    for (size_t i = 0; i < lines->length; i++) {
        Token temp = parseLineToToken(lines->entries[i]);
        TokenLine* tokenLine = saveTokenLine(temp, lines->entries[i]);
        string* tokenStr = tokenToStr(temp);
        printf("token: %s, line: %s\n", tokenStr->data, tokenLine->line->data);
        strFree(tokenStr);
        tokenLineFree(tokenLine);
    }
    strFree(file);
    strFree(preppedFile);
    strArrFree(lines);
    // sleep(10);
    return 0;
}
