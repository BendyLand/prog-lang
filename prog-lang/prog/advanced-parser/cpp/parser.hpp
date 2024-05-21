#include <vector>
#include "variables.hpp"

#ifndef PARSER_H
#define PARSER_H

class Parser {
public:
    Parser(Variables &vars);
    void serveKeywordToken(std::vector<std::string>);

private:
    Variables &_vars;
};

std::vector<std::string> parseVariableLine(std::vector<std::string>);

#endif