#include <vector>
#include <sstream>
#include "parser.hpp"
#include "lexer.hpp"
#include "variables.hpp"

using namespace std;

Parser::Parser() {}

Value evaluateArithmeticExpression(string expr) 
{
    Value result;
    cout << "expression: " << expr << endl;
    //* THIS IS WHERE I LEFT OFF

    return Value();
}

void parseVariableLine(vector<string> tokens)
{
    string operators[] = {"+", "-", "*", "/", "%"};
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
    if (count > 1) { // if it's not a string variable
        for (string item : operators) {
            if (expr.find(item) != string::npos) {
                exprType = "arithmetic";
                goto BreakA;
            }
        }
    }
    exprType = "variable";
    BreakA:
    if (exprType.compare("arithmetic") == 0)
        evaluateArithmeticExpression(expr);
}

void Parser::serveKeywordToken(vector<string> tokens) 
{
    tokens = removeEmptyTokens(tokens);
    if (tokens[0].compare("print") == 0)
        cout << tokens[1];
    else if (tokens[0].compare("puts") == 0) 
        cout << tokens[1] << endl;
    else if (tokens[0].compare("let") == 0) 
        parseVariableLine(tokens);
    // else if (tokens[0].compare("if") == 0)
    //     cout << "I'm in the `if` branch" << endl;
    // else if (tokens[0].compare("for") == 0)
    //     cout << "I'm in the `for` branch" << endl;
    // else
    //     cout << "This line doesn't have a keyword" << endl;
}

