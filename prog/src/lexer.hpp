#ifndef LEXER_HPP
#define LEXER_HPP

#include "utils.hpp" // iostream, string, fstream, vector
#include "symbols.hpp"
#include <boost/regex.hpp>

std::string prepareFile(std::string file);
std::string normalize(std::string file);
std::string removeComments(std::string file);
std::string removeEmptyLines(std::string file);
std::string extractVarName(std::string line);
AnyType extractVarValue(std::string line);
AnyType inferType(std::string original);
// boost::regex pat(R"(\(?\-?\d+(.\d+)?([\+\-\*/]\*?\(?\d+(.\d+)?\)?)+)"); pattern to match arithmetic
#endif