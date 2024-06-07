#ifndef UTILS_H
#define UTILS_H

#include <algorithm> 
#include <cctype>
#include <locale>

/** Trim whitespace from string start (in place) */
void ltrim(std::string &s);

/** Trim whitespace from string end (in place) */
void rtrim(std::string &s);
#endif 