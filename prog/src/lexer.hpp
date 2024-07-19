#ifndef LEXER_HPP
#define LEXER_HPP

#include <boost/regex.hpp>
#include "utils.hpp" // iostream, string, fstream, vector
#include "symbols.hpp" // iostream, unordered_map, variant

std::string prepareFile(std::string file);
std::string normalize(std::string file);
std::string removeComments(std::string file);
std::string removeEmptyLines(std::string file);
std::string extractVarName(std::string line);
std::string inferType(std::string original);
AnyType extractVarValue(std::string line);
AnyType parseValIntoType(std::string val, std::string type);
// boost::regex pat(R"(\(?\-?\d+(.\d+)?([\+\-\*/]\*?\(?\d+(.\d+)?\)?)+)"); pattern to match arithmetic
#endif