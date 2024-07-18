#include "symbols.hpp"

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
    std::cout << "Current Variables:" << std::endl;
    size_t i = this->m_vars.size();
    for (auto& var : this->m_vars) {
        std::cout << i << ".) " << var.first << ": " << var.second;
        i--;
    }
}