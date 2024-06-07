#include <iostream>
#include <regex>
#include "lexer.hpp" // <vector>
#include "parser.hpp" // <vector>
#include "utils.hpp" // <algorithm>, <cctype>, <locale>
#include "tokens.hpp" // <string>

Parser::Parser(Variables &vars) :
    _vars(vars)
{}



