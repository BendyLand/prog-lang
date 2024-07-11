#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::string readFile(std::string path);
std::vector<std::string> strSplit(std::string text, std::string delim);
bool containsEmbeddedString(std::string src);
std::string lstrip(std::string original);

#endif