#include <unordered_map>
#include <iostream>
#include <variant>
#include "variables.hpp"

using namespace std;

using Value = variant<int, double, char, string, bool>;
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

Variables::Variables() : _count(0) {}

unordered_map<string, Value>& Variables::add(string name, Value item) 
{
    _variables.insert_or_assign(name, item);
    _count++;
    return _variables;
}

unordered_map<string, Value>& Variables::remove(string name)
{
    _variables.erase(name);
    _count--;
    return _variables;
}

void Variables::show()
{
    for (auto &[key, val] : _variables) {
        cout << "Name: " << key << ", Value: " << val << endl;
    }
}
