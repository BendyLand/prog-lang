#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <iostream>
#include <boost/regex.hpp>

std::vector<std::string> extractInnerVariables(std::string text);
bool containsInnerVariables(std::string text);
bool executePrint(std::string text);

#endif