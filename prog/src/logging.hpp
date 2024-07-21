#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <boost/regex.hpp>
#include "utils.hpp" // "symbols.hpp" -> iostream, unordered_map, variant; string, fstream, vector

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
bool contains_multiple_args(std::string text);
std::vector<std::string> extract_inner_str_variables(std::string text);
bool contains_inner_variables(std::string text);
void execute_print(std::string text);
std::string extract_text_from_string(std::string original);
std::string handle_escape_chars(std::string text);

#endif