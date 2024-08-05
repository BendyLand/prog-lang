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
    // To store the initially parsed lines
    size_t len = lines->length;
    TokenLine* tokenLines[len];
    for (size_t i = 0; i < lines->length; i++) {
        Token temp = parseLineToToken(lines->entries[i]);
        TokenLine* tokenLine = saveTokenLine(temp, lines->entries[i]);
        // For conditional branches that start with }
        validateTokenLine(&tokenLine);
        string* tokenStr = tokenToStr(tokenLine->token);
        tokenLines[i] = tokenLine;
        strFree(tokenStr);
    }
    processTokensFirstPass(&lines, &tokenLines);
    processTokensSecondPass(&tokenLines, len);
    processTokensThirdPass(&tokenLines, &len);
    for (size_t i = 0; i < len; i++) {
        string* token = tokenToStr(tokenLines[i]->token);
        if (tokenLines[i]->line->length > 0) {
            printf("%s : %s\n", token->data, tokenLines[i]->line->data);
        }
        else {
            printf("%s\n", token->data);
        }
        tokenLineFree(tokenLines[i]);
        strFree(token);
    }
    strFree(file);
    strFree(preppedFile);
    strArrFree(lines);
    // sleep(10);
    return 0;
}
