#include <iostream>
#include <regex>
#include "parser.hpp" // includes <vector>
#include "lexer.hpp"
#include "utils.hpp" // includes <algorithm>, <cctype>, <locale>
#include "variables.hpp" // includes <unordered_map> and <variant>

bool checkForStringInterpolation(std::string);
std::vector<std::string> findVariablesInString(std::string);
std::string insertVariableIntoStringInterpolation(std::string, Variables);

Parser::Parser(Variables &vars) :
    _vars(vars)
{}

std::string removeSpacesFromExpression(std::string expr)
{
    std::string newStr = "";
    for (int i = 0; i < expr.size(); i++) {
        if (expr[i] != ' ')
            newStr += expr[i];
    }
    return newStr;
}

std::vector<std::string> parseVariableLine(std::vector<std::string> tokens)
{
    std::string varName = tokens[1];
    std::string expr = "";
    std::string exprType = "";
    size_t count = 0;
    bool isExpr = false;

    for (std::string token : tokens) {
        if (isExpr) {
            expr += token + " ";
            count++;
        }
        if (token == "=")
            isExpr = true;
    }
    rtrim(expr);
    return {varName, expr};
}


std::string insertVariableIntoStringInterpolation(std::string str, Variables vars) 
{
    std::vector<std::string> varNames = findVariablesInString(str);
    std::string newString = "";
    std::string currentVarName = "";
    bool isVar = false;
    int varIndex = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (isVar) {
            if (str[i] == '}') {
                Value val = vars.getVar(currentVarName);
                std::string temp = "";
                temp += val;
                newString += val;
                isVar = false;
                currentVarName = "";
                i++;
            } 
            else {
                currentVarName += str[i];
            }
        } 
        else {
            if (str[i] == '$' && i + 1 < str.size() && str[i + 1] == '{') {
                isVar = true;
                i++; 
            } 
            else {
                newString += str[i];
            }
        }
    }
    return newString;
}


std::vector<std::string> findVariablesInString(std::string str)
{
    std::regex pattern (R"(\$\{([^}]*)\})");
    std::smatch matches;
    std::vector<std::string> results;
    while (std::regex_search(str, matches, pattern)) {
        if (matches.size() > 1) {
            results.push_back(matches[1].str());
        }
        str = matches.suffix().str();
    }
    return results;
}

bool checkForStringInterpolation(std::string str)
{
    std::regex pattern (R"(\$\{[^}]*\})");
    std::smatch matches;
    bool result = std::regex_search(str, matches, pattern);
    return result;
}