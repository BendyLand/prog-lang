#include "utils.hpp" // "symbols.hpp" -> iostream, unordered_map, variant; string, fstream, vector

std::string read_file(std::string path)
{
    std::ifstream file(path);
    std::string result;
    char c;
    while (file) {
        c = file.get();
        if (c > 0) {
            result += c;
        }
    }
    file.close();
    return result;
}

std::vector<std::string> split(std::string text, std::string delim)
{
    size_t pos = 0;
    std::string token;
    std::vector<std::string> result;
    while ((pos = text.find(delim)) != std::string::npos) {
        token = text.substr(0, pos);
        result.push_back(token);
        text.erase(0, pos + delim.size());
    }
    if (text.size() > 0) {
        result.push_back(text);
    }
    return result;
}

bool contains_embedded_string(std::string src)
{
    size_t first = src.find_first_of("\"");
    size_t last = src.find_last_of("\"");
    return (first != last) && (first != std::string::npos);
}

bool contains(std::string haystack, std::string needle)
{
    return haystack.find(needle) != std::string::npos;
}

std::string lstrip(std::string original)
{
    std::string result = "";
    for (char c : original) {
        if (result.size() == 0 && isspace(c)) {
            continue;
        }
        result += c;
    }
    return result;
}

std::string reverse(std::string original)
{
    std::string result = "";
    for (int i = original.size()-1; i >= 0; i--) {
        result += original[i];
    }
    return result;
}

std::string rstrip(std::string original)
{
    if (!original.ends_with(" ")) {
        return original;
    }
    std::string temp = reverse(original);
    temp = lstrip(temp);
    std::string result = reverse(temp);
    return result;
}

std::string strip(std::string original)
{
    std::string result = original;
    result = rstrip(original);
    return lstrip(result);
}

std::string remove_inner_whitespace(std::string original)
{
    std::string result = "";
    for (char c : original) {
        if (!isspace(c)) {
            result += c;
        }
    }
    return result;
}

size_t count(std::string str, char c)
{
    size_t result = 0;
    for (char ch : str) {
        if (c == ch) result++;
    }
    return result;
}

std::string get_var_type(AnyType var)
{
    std::string result = "";
    if (holds_alternative<int>(var)) {
        result = "int";
    }
    else if (holds_alternative<double>(var)) {
        result = "double";
    }
    else if (holds_alternative<char>(var)) {
        result = "char";
    }
    else if (holds_alternative<std::string>(var)) {
        result = "str";
    }
    else if (holds_alternative<bool>(var)) {
        result = "bool";
    }
    return result;
}

bool contains_any(std::string haystack, std::vector<std::string> needles)
{
    for (std::string needle : needles) {
        if (haystack.find(needle) != std::string::npos) {
            return true;
        }
    }
    return false;
}
