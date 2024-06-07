#include <iostream>
#include "variables.hpp" // <unordered_map>, <variant>

// using Value = std::variant<int, double, char, std::string, bool>;
// Overload operator<< for Value
std::ostream& operator<<(std::ostream& os, const Value& v) {
    // Use std::visit to handle each possible type in the variant
    std::visit([&os](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, bool>)
            os << (arg ? "true" : "false"); 
        else
            os << arg; 
    }, v);
    return os;
}

std::string& operator+=(std::string& str, const Value& v) {
    // Use std::visit to handle each possible type in the variant
    std::visit([&str](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, bool>) 
            str += (arg ? "true" : "false"); 
        else if constexpr (std::is_same_v<T, int>)
            str += std::to_string(arg);
        else if constexpr (std::is_same_v<T, double>)
            str += std::to_string(arg);
        else 
            str += arg;
    }, v);
    return str;
}

Variables::Variables() : 
    _count(0) 
{}

std::unordered_map<std::string, Value>& Variables::add(std::string name, Value item) 
{
    _variables.insert_or_assign(name, item);
    _count++;
    return _variables;
}

std::unordered_map<std::string, Value>& Variables::remove(std::string name)
{
    _variables.erase(name);
    _count--;
    return _variables;
}

void Variables::show()
{
    std::cout << "Variables: " << std::endl;
    for (auto &[key, val] : this->_variables) {
        std::cout << "Name: " << key << ", Value: " << val << std::endl;
    }
}

Value Variables::getVar(std::string name) 
{
    auto it = this->_variables.find(name);
    if (it != this->_variables.end()) {
        return it->second;
    }
    return "";
}

void Variables::setVar(const std::string& varName, const std::string& value) 
{
    this->_variables[varName] = value;
}