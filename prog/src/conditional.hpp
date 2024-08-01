#pragma once

#include <iostream>
#include "utils.hpp"

std::string extract_conditional_expr(std::string line);
std::vector<std::string> extract_boolean_expr_variables(std::string text);
bool evaluate_conditional(std::string expr, SymbolTable symbols);

