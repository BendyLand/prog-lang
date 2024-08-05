#pragma once

#include <stdio.h>
#include "str.h"
#include "utils.h"

typedef enum 
{
    LET,
    PRINT,
    PUTS,
    IF,
    ELIF,
    ELSE,
    FOR,
    END_BLOCK,
    START_BLOCK,
    NA
} Token;

typedef struct
{
	Token token;
	string* line;
} TokenLine;

Token parseLineToToken(string* line);
string* tokenToStr(Token token);
TokenLine* saveTokenLine(Token token, string* line);
void tokenLineFree(TokenLine* line);
void validateTokenLine(TokenLine** tokLine);
string* extractCondition(TokenLine* tokLine);
string* removeFirstToken(TokenLine* tokLine);
void shiftTokenLines(TokenLine** tokenLines, size_t idx, size_t len);

/**
 * Formats the text associated with each token line.
 * @param tokenLines The set of token lines to process.
 * @param len The number of token lines.
 */
void processTokensFirstPass(TokenLine** tokenLines, size_t len);

/**
 * Assigns NA to unnecessary token lines.
 * @param tokenLines The set of token lines to process.
 * @param len The number of token lines.
 */
void processTokensSecondPass(TokenLine** tokenLines, size_t len);

/**
 * Removes NA token lines from the array and adds a NULL element. `len` is decremented to keep track of the current element.
 * @param tokenLines The set of token lines to process.
 * @param len A *pointer* to the number of token lines.
 */
void processTokensThirdPass(TokenLine** tokenLines, size_t* len);

/**
 * Calls the first three passes of processToken.
 * @param tokenLines An array of token lines.
 * @param len A *pointer* to the number of token lines.
 */
void processTokensInitial(TokenLine** tokenLines, size_t* len);