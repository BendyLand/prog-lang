#ifndef LEXER_HPP
#define LEXER_HPP

#include "utils.hpp" // iostream, string, fstream, vector

std::string prepareFile(std::string file);
std::string normalize(std::string file);
std::string removeComments(std::string file);
std::string removeEmptyLines(std::string file);

#endif