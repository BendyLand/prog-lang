#include <string>
#include "utils.hpp" // includes <algorithm>, <cctype>, <locale>

/** trim from start (in place) */
void ltrim(std::string &s) 
{
    int firstNonWhitespace = 0;
    while (firstNonWhitespace < s.size() && s[firstNonWhitespace] == ' ') {
        firstNonWhitespace++;
    }
    s = s.substr(firstNonWhitespace);
}

/** trim from end (in place) */
void rtrim(std::string &s) 
{
    int lastNonWhitespace = s.size() - 1;
    while (lastNonWhitespace >= 0 && s[lastNonWhitespace] == ' ') {
        lastNonWhitespace--;
    }
    s = s.substr(0, lastNonWhitespace+1);
}