#include <iostream>
#include <regex>
#include "lexer.hpp" 
#include "parser.hpp" // lexer.hpp and parser.hpp includes <vector>
#include "utils.hpp" // includes <algorithm>, <cctype>, <locale>

Parser::Parser(Variables &vars) :
    _vars(vars)
{}



