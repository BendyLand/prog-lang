#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <iostream>
#include <unordered_map>
#include <variant>

using AnyType = std::variant<int, double, bool, char, std::string>;
using Variables = std::unordered_map<std::string, AnyType>;

class SymbolTable
{
public:
    SymbolTable(Variables vars);
    Variables get_g_vars();
    void display_l_vars_list();
    void add_l_var(std::string name, AnyType val, std::string l_var_name);
    void pop_l_vars(std::string vars);
    void cleanup_l_vars();
    void new_l_vars(std::string name);
    std::optional<Variables> get_l_vars_list(std::string name);
    std::optional<AnyType> get_val(std::string name);
    bool contains_all(std::vector<std::string> found_vars);
    void display_g_vars();
    void add_var(std::string name, AnyType value);
    inline std::string any_to_string(AnyType val);

private:
    Variables m_g_vars;
    std::unordered_map<std::string, Variables> m_l_vars;
};

inline std::ostream& operator<<(std::ostream& os, const AnyType& any)
{
    if (std::holds_alternative<int>(any)) {
        os << std::get<int>(any) << std::endl;
    }
    else if (std::holds_alternative<double>(any)) {
        os << std::get<double>(any) << std::endl;
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

inline std::string any_to_string(AnyType val)
{
    std::string result;
    if (std::holds_alternative<int>(val)) {
        result = std::to_string(std::get<int>(val));
    }
    else if (std::holds_alternative<double>(val)) {
        result = std::to_string(std::get<double>(val));
    }
    else if (std::holds_alternative<char>(val)) {
        result = std::to_string(std::get<char>(val));
    }
    else if (std::holds_alternative<std::string>(val)) {
        result = std::get<std::string>(val);
    }
    else if (std::holds_alternative<bool>(val)) {
        result = std::to_string(std::get<bool>(val));
    }
    return result;
}

#endif