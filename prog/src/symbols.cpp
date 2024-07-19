#include "symbols.hpp"
#include "utils.hpp"

SymbolTable::SymbolTable(Variables vars) : m_vars(vars)
{}

Variables SymbolTable::getVars()
{
    return this->m_vars;
}

void SymbolTable::addVar(std::string name, AnyType value)
{
    this->m_vars.insert_or_assign(name, value);
}

void SymbolTable::displayVars()
{
    std::cout << "\nCurrent Variables:" << std::endl << std::endl;
    size_t i = this->m_vars.size();
    for (auto& var : this->m_vars) {
        std::string varType = getVarType(var.second);
        std::cout << "Name: " << var.first << std::endl;
        std::cout << "Value: " << var.second; 
        std::cout << "Type: " << varType << std::endl << std::endl;
        i--;
    }
}