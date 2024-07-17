#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <iostream>
#include <unordered_map>
#include <variant>

using AnyType = std::variant<int, float, bool, char, std::string>;
using Variables = std::unordered_map<std::string, AnyType>;

class SymbolTable
{
public:
    SymbolTable(Variables vars);
    Variables getVars();
    void displayVars();
    void addVar(std::string name, AnyType value);

private:
    Variables m_vars;
};

inline std::ostream& operator<<(std::ostream& os, const AnyType& any)
{
    if (std::holds_alternative<int>(any)) {
        os << std::get<int>(any) << std::endl;
    }
    else if (std::holds_alternative<float>(any)) {
        os << std::get<float>(any) << std::endl;
    }
    else if (std::holds_alternative<char>(any)) {
        os << std::get<char>(any) << std::endl;
    }
    else if (std::holds_alternative<std::string>(any)) {
        os << std::get<std::string>(any) << std::endl;
    }
    else if (std::holds_alternative<bool>(any)) {
        os << (std::get<bool>(any) ? "true" : "false") << std::endl;
    }
    return os;
}

#endif