#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <variant>
#include "symbols.hpp" // iostream, unordered_map, variant

std::string lstrip(std::string original);
std::string rstrip(std::string original);
std::string strip(std::string original);
std::string remove_inner_whitespace(std::string original);
std::string read_file(std::string path);
std::vector<std::string> split(std::string text, std::string delim);
bool contains_embedded_string(std::string src);
bool contains(std::string haystack, std::string needle);
size_t count(std::string str, char c);
std::string get_var_type(AnyType var);
bool contains_any(std::string haystack, std::vector<std::string> needles);
bool contains_key(std::unordered_map<std::string, AnyType> haystack, std::string needle);

template<typename T>
bool contains(std::vector<T> vec, T item)
{
    for (auto &entry : vec) {
        if (entry == item) {
            return true;
        }
    }
    return false;
}

template<typename T>
std::vector<T> dedup(std::vector<T> original)
{
    std::vector<T> result;
    for (size_t i = 0; i < original.size(); i++) {
        if (contains(result, original[i])) {
            continue;
        }
        result.push_back(original[i]);
    }
    return result;
}

#endif