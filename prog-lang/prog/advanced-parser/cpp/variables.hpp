#include <unordered_map>
#include <variant>
#include "lexer.hpp"

#ifndef VARIABLE_H
#define VARIABLE_H

using Value = std::variant<int, double, char, std::string, bool>;

std::ostream& operator<<(std::ostream& os, const Value& v);
std::string& operator+=(std::string& str, const Value& v);

class Variables {
public:
    Variables();
    std::unordered_map<std::string, Value>& add(std::string name, Value item);
    std::unordered_map<std::string, Value>& remove(std::string name);
    Value getVar(std::string);
    void setVar(const std::string& varName, const std::string& value);
    void show();

private:
    /** 
     * Private unordered map to store all the variables.
     */
    std::unordered_map<std::string, Value> _variables;
    /** 
     * Private size_t of the current number of variables.
     */
    size_t _count;
};

#endif