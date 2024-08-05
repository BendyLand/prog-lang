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
        result = O_BRACE;
    }
    else if (strContainsStr(words->entries[0], "}")) {
        result = C_BRACE;
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
    case C_BRACE:
        result = str("C_BRACE");
        break;
    case O_BRACE:
        result = str("O_BRACE");
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
    if ((*tokLine)->token == C_BRACE) {
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
        string* temp = tokenToStr(tokenLines[i]->token);
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
        printf("Token: %s, Line: %s\n", temp->data, tokenLines[i]->line->data);
        strFree(temp);
        tokenLineFree(tokenLines[i]);
    }
}