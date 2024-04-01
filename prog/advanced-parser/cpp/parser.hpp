#include <vector>

#ifndef PARSER_H
#define PARSER_H

class Parser {
public:
    Parser();
    void serveKeywordToken(std::vector<std::string>);
};

void parseVariableLine(std::vector<std::string>);

#endif