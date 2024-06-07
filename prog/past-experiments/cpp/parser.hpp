#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "variables.hpp"

class Parser {
public:
    Parser(Variables &vars);

private:
    /** 
     * The Variables object contains a private unordered map to keep track of 
     * the variables in the program.
     */
    Variables &_vars;
};

#endif