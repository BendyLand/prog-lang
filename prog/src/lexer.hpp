#pragma once

#include "arithmetic.hpp" 
#include "conditional.hpp"
#include "logging.hpp" 
#include "symbols.hpp" 
#include "utils.hpp" 

std::string prepare_file(std::string file);
std::string normalize(std::string file);
std::string remove_comments(std::string file);
std::string remove_empty_lines(std::string file);
std::string extract_var_name(std::string line);
std::string infer_type(std::string original);
AnyType extract_var_value(std::string line, SymbolTable symbols);
AnyType parse_val_into_type(std::string val, std::string type, SymbolTable symbols);
// boost::regex pat(R"(\(?\-?\d+(.\d+)?([\+\-\*/]\*?\(?\d+(.\d+)?\)?)+)"); pattern to match arithmetic
