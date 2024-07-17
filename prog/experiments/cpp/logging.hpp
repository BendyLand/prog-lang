#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <iostream>
#include <boost/regex.hpp>

/**
 * @brief Checks the given text for multiple arguments.
 * @param text The string to check.

 * @note For now, to print multiple args, the first one must be a string, 
 * even if it is just a variable: 
 * @note WRONG: puts var1, var2
 * @note WRONG: puts var1, "${var2}"
 * @note RIGHT: puts "any regular string", var1, var2
 * @note RIGHT: puts "${var1} ${var2}"
 * @note RIGHT: puts "${var1}", var2
 * @note RIGHT: puts "", var1, var2
 */
bool containsMultipleArgs(std::string text);
std::vector<std::string> extractInnerVariables(std::string text);
bool containsInnerVariables(std::string text);
bool executePrint(std::string text);
std::string extractTextFromString(std::string original);

#endif