#include "utils.hpp" // "symbols.hpp" -> iostream, unordered_map, variant; string, fstream, vector

SymbolTable::SymbolTable(Variables vars) : m_vars(vars)
{}

Variables SymbolTable::get_vars()
{
    return this->m_vars;
}

void SymbolTable::add_var(std::string name, AnyType value)
{
    this->m_vars.insert_or_assign(name, value);
}

void SymbolTable::display_vars()
{
    std::cout << "\nCurrent Variables:" << std::endl << std::endl;
    size_t i = this->m_vars.size();
    for (auto& var : this->m_vars) {
        std::string varType = get_var_type(var.second);
        std::cout << "Name: " << var.first << std::endl;
        std::cout << "Value: " << var.second; 
        std::cout << "Type: " << varType << std::endl << std::endl;
        i--;
    }
}