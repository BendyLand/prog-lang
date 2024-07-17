#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::string lstrip(std::string original);
std::string rstrip(std::string original);
std::string readFile(std::string path);
std::vector<std::string> split(std::string text, std::string delim);
bool containsEmbeddedString(std::string src);
bool contains(std::string haystack, std::string needle);

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