#include <vector>
#include <variant>
#include <optional>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <string>
#include "parser.hpp"
#include "lexer.hpp"
#include "variables.hpp"

using namespace std;

using Number = variant<int, double>;

double evaluateDoubleExpression(string);
int evaluateIntegerExpression(string);
Number evaluateExpression(string, bool, bool, bool, bool);
void chooseIntOperator(int&, optional<int>, optional<int>, string);

Parser::Parser() {}

Number evaluateExpression(string expr, bool fst, bool snd, bool thrd, bool frth)
{
    Number result;
    if (!fst && !snd && !thrd && !frth) {
        if (expr.find('.') != string::npos) {
            result = evaluateDoubleExpression(expr);
        }
        else {
            if (!expr.empty()) {
                result = evaluateIntegerExpression(expr);
            }
        }
    }
    return result;
}

void chooseIntOperator(int& finalResult, optional<int> num1, optional<int> num2, string op)
{
    if (num1 && num2) {
        int n1 = num1.value();
        int n2 = num2.value();
        if (op.size() > 1) {
            finalResult = pow(n1, n2);
        }
        switch (op[0]) {
        case '+':
            finalResult = n1 + n2;
            break;
        case '-':
            finalResult = n1 - n2;
            break;
        case '*':
            finalResult = n1 * n2;
            break;
        case '/':
            if (n2 != 0)
                finalResult = n1 / n2;
            else
                finalResult = 0;
            break;
        }
    }
}

double evaluateDoubleExpression(string expr)
{
    return 1.0;
}

int evaluateIntegerExpression(string expr)
{
    int finalResult;
    optional<int> num1;
    optional<int> num2;
    optional<int> res1;
    optional<int> res2;
    optional<int> res3;

    string temp = "";
    string op = "";
    istringstream iss(expr);
    char c;
    while (iss >> c) {
        if (c == '*' && num1) {
            op += c;
            continue;
        }
        if (isdigit(c) && !num1) {
            temp += c;
        }
        if (!isdigit(c) && !num1) {
            try {
                num1 = stoi(temp);
                temp = "";
                op += c;
                continue;
            }
            catch (invalid_argument e) {
                cout << "Something went wrong for num1: " << e.what();
            }
        }
        if (num1 && op.size() >= 1) {
            temp += c;
        }
    }
    try {
        num2 = stoi(temp);
    }
    catch (invalid_argument e) {
        cout << "Something went wrong for num2: " << e.what() << endl;
    }

    chooseIntOperator(finalResult, num1, num2, op);
    return finalResult;
}

string removeSpacesFromExpression(string expr)
{
    string newStr = "";
    for (int i = 0; i < expr.size(); i++) {
        if (expr[i] != ' ')
            newStr += expr[i];
    }
    return newStr;
}

Value evaluateArithmeticExpression(string expr)
{
    expr = removeSpacesFromExpression(expr);
    bool firstPass = false;
    bool secondPass = false;
    bool thirdPass = false;
    bool fourthPass = false;
    Value result;
    // Operations: PEMDAS
    string currentExpr = "";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < expr.size(); j++) {
            if (i == 0) {
                if (expr[j] == '(') {
                    firstPass = true;
                    continue;
                }
                if (expr[j] == ')') {
                    firstPass = false;
                }
            }
            if (firstPass) {
                currentExpr += expr[j];
            }

            Number exprVal = evaluateExpression(
                                currentExpr,
                                firstPass,
                                secondPass,
                                thirdPass,
                                fourthPass
                            );
            if (holds_alternative<int>(exprVal)) {
                cout << "exprValue: " << get<int>(exprVal) << endl;
            }
            else {
                cout << "exprValue: " << get<double>(exprVal) << endl;
            }
            // Make `swapEvaluatedExpression` function to plug it back into the string

            // Once the expression is evaluated,
            // it needs to re-inserted into the expression.

            // if (i == 1) {
            //     if (j < expr.size()-3) {
            //         if (expr[j+1] == '*' && expr[j+2] == '*') {
            //             secondPass = true;
            //         }
            //     }
            // }
            // if (secondPass) {
            //     currentEval += " ";
            //     for (int n = j; n < j+3; n++)
            //         currentEval += expr[n];
            //     currentEval += " ";
            //     secondPass = false;
            // }
        }
    }
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

