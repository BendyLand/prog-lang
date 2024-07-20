#pragma once

#include <boost/regex.hpp>
#include "utils.hpp" // iostream, string, fstream, vector
#include "symbols.hpp" // iostream, unordered_map, variant

std::string prepare_file(std::string file);
std::string normalize(std::string file);
std::string remove_comments(std::string file);
std::string remove_empty_lines(std::string file);
std::string extract_var_name(std::string line);
std::string infer_type(std::string original);
AnyType extract_var_value(std::string line);
AnyType parse_val_into_type(std::string val, std::string type);
// boost::regex pat(R"(\(?\-?\d+(.\d+)?([\+\-\*/]\*?\(?\d+(.\d+)?\)?)+)"); pattern to match arithmetic
