#include <iostream>
#include "parser.hpp" // includes <vector>
#include "lexer.hpp"

using namespace std;

Parser::Parser(Variables &vars) :
    _vars(vars)
{}

string removeSpacesFromExpression(string expr)
{
    string newStr = "";
    for (int i = 0; i < expr.size(); i++) {
        if (expr[i] != ' ')
            newStr += expr[i];
    }
    return newStr;
}

vector<string> parseVariableLine(vector<string> tokens)
{
    string varName = tokens[1];
    string expr = "";
    string exprType = "";
    size_t count = 0;
    bool isExpr = false;

    for (string token : tokens) {
        if (isExpr) {
            expr += token + " ";
            count++;
        }
        if (token == "=")
            isExpr = true;
    }
    return {varName, expr};
}

void Parser::serveKeywordToken(vector<string> tokens)
{
    tokens = removeEmptyTokens(tokens);
    if (tokens[0].compare("print") == 0) {
        cout << tokens[1];
    }
    else if (tokens[0].compare("puts") == 0) {
        cout << tokens[1] << endl;
    }
    else if (tokens[0].compare("let") == 0) {
        vector<string> item = parseVariableLine(tokens);
        this->_vars.add(item[0], Value(item[1]));
    }
    // else if (tokens[0].compare("if") == 0)
    //     cout << "I'm in the `if` branch" << endl;
    // else if (tokens[0].compare("for") == 0)
    //     cout << "I'm in the `for` branch" << endl;
    // else
    //     cout << "This line doesn't have a keyword" << endl;
}
