#include <unordered_map>
#include <iostream>
#include <variant>
#include "lexer.hpp"

#ifndef VARIABLE_H
#define VARIABLE_H

using Value = std::variant<int, double, char, std::string, bool>;

std::ostream& operator<<(std::ostream& os, const Value& v);

class Variables {
public:
    Variables();
    std::unordered_map<std::string, Value>& add(std::string name, Value item);
    std::unordered_map<std::string, Value>& remove(std::string name);
    void show();

private:
    std::unordered_map<std::string, Value> _variables;
    size_t _count;
};

#endif