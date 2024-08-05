#include "token.h"

Token parseLineToToken(string* line)
{
    Token result;
    stringArray* words = strArr(line, " ");
    if (strContainsStr(words->entries[0], "let")) {
        result = LET;
    }
    else if (strContainsStr(words->entries[0], "print")) {
        result = PRINT;
    }
    else if (strContainsStr(words->entries[0], "puts")) {
        result = PUTS;
    }
    else if (strContainsStr(words->entries[0], "elif")) {
        result = ELIF;
    }
    else if (strContainsStr(words->entries[0], "if")) {
        result = IF;
    }
    else if (strContainsStr(words->entries[0], "else")) {
        result = ELSE;
    }
    else if (strContainsStr(words->entries[0], "for")) {
        result = FOR;
    }
    else if (strContainsStr(words->entries[0], "{")) {
        result = START_BLOCK;
    }
    else if (strContainsStr(words->entries[0], "}")) {
        result = END_BLOCK;
    }
    else {
        result = NA;
    }
    strArrFree(words);
    return result;
}

string* tokenToStr(Token token)
{
    string* result;
    switch (token) {
    case LET:
        result = str("LET");
        break;
    case PRINT:
        result = str("PRINT");
        break;
    case PUTS:
        result = str("PUTS");
        break;
    case IF:
        result = str("IF");
        break;
    case ELIF:
        result = str("ELIF");
        break;
    case ELSE:
        result = str("ELSE");
        break;
    case FOR:
        result = str("FOR");
        break;
    case END_BLOCK:
        result = str("END_BLOCK");
        break;
    case START_BLOCK:
        result = str("START_BLOCK");
        break;
    default:
        result = str("NA");
        break;
    }
    return result;
}

TokenLine* saveTokenLine(Token token, string* line)
{
    TokenLine* result = (TokenLine*)malloc(sizeof(TokenLine));
    result->token = token;
    string* temp = strCopy(line);
    result->line = temp;
    return result;
}

void tokenLineFree(TokenLine* line)
{
    if (line) {
        if (line->line) {
            strFree(line->line);
        }
        free(line);
    }
}

void validateTokenLine(TokenLine** tokLine)
{
    if ((*tokLine)->token == END_BLOCK) {
        if (strContainsStr((*tokLine)->line, "elif")) {
            (*tokLine)->token = ELIF;
        }
        else if (strContainsStr((*tokLine)->line, "else")) {
            (*tokLine)->token = ELSE;
        }
    }
}

string* extractCondition(TokenLine* tokLine)
{
    string* result;
    if (tokLine->line->length > 1) {
        int start;
        if (tokLine->line->data[0] != '}') {
            start = indexOf(tokLine->line, ' ');
        }
        else {
            start = indexOfStr(tokLine->line, "elif");
            start += 5;
        }
        int end = indexOf(tokLine->line, '{');
        if (end == -1) end = (int)tokLine->line->length+1;
        result = substr(tokLine->line, start, end);
    }
    else {
        result = strCopy(tokLine->line);
    }
    lstrip(result);
    return result;
}

string* removeFirstToken(TokenLine* tokLine)
{
    string* result;
    int start = indexOf(tokLine->line, ' ');
    int end = (int)tokLine->line->length+1;
    result = substr(tokLine->line, start, end);
    lstrip(result);
    return result;
}

void processTokensFirstPass(stringArray** lines, TokenLine** tokenLines)
{
    for (size_t i = 0; i < (*lines)->length; i++) {
        string* token = tokenToStr(tokenLines[i]->token);
        if (tokenLines[i]->token == IF || tokenLines[i]->token == ELIF || tokenLines[i]->token == FOR) {
            string* condition = extractCondition(tokenLines[i]);
            strFree(tokenLines[i]->line);
            tokenLines[i]->line = condition;
        }
        else {
            if (tokenLines[i]->token != ELSE) {
                string* temp = removeFirstToken(tokenLines[i]);
                strFree(tokenLines[i]->line);
                tokenLines[i]->line = temp;
            }
            else {
                strClear(tokenLines[i]->line);
            }
        }
        strFree(token);
    }
}

void processTokensSecondPass(TokenLine** tokenLines, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        if (tokenLines[i]->token == START_BLOCK) {
            tokenLines[i]->token = NA;
            continue;
        }
        if (i < len-1) {
            if (tokenLines[i]->token == END_BLOCK) {
                if (tokenLines[i+1]->token == ELIF || tokenLines[i+1]->token == ELSE) {
                    tokenLines[i]->token = NA;
                }
            }
        }
    }
}

void shiftTokenLines(TokenLine** tokenLines, size_t idx, size_t len)
{
    if (idx >= len) return;
    tokenLineFree(tokenLines[idx]);
    for (size_t i = idx; i < len-1; i++) {
        tokenLines[i] = tokenLines[i+1];
    }
    tokenLines[len-1] = NULL;
}

void processTokensThirdPass(TokenLine** tokenLines, size_t* len)
{
    size_t count = 0;
    size_t i = 0;
    while (i < (*len)-1) {
        if (tokenLines[i]->token == NA) {
            shiftTokenLines(tokenLines, i, (*len));
            (*len)--;
        }
        else {
            i++;
        }
    }
}
