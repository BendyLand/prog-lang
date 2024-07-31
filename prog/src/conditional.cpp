#include "conditional.hpp"

std::string extract_conditional_expr(std::string line)
{
    size_t start = 0;
    if (contains(line, "elif")) {
        start = line.find("elif") + 4;
    }
    else if (contains(line, "if")) {
        start = line.find("if") + 2;
    }
    size_t len = 0;
    if (contains(line, "{")) {
        len = line.find("{") - start;
    }
    else {
        len = line.size();
    }
    std::string result = line.substr(start, len);
    return strip(result);
}

