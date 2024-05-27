#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "variables.hpp"

class Parser {
public:
    Parser(Variables &vars);
    void serveKeywordToken(std::vector<std::string>, Variables);

private:
    /** 
     * The Variables object contains a private unordered map to keep track of 
     * the variables in the program.
     */
    Variables &_vars;
};

std::vector<std::string> parseVariableLine(std::vector<std::string>);

#endif