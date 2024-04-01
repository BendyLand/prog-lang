#include <variant>
#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>
#include "arithmetic.hpp"

using namespace std;
using Number = variant<int, double>;

string reduceInnerExpression(string nestedExpr)
{
    bool inner = false;
    vector<string> pieces;
    string temp = "";
    string innerExpr = "";
    for (int i = 0; i < nestedExpr.size(); i++) {
        if (inner) {
            if (nestedExpr[i] == ')') {
                innerExpr += nestedExpr[i];
                pieces.push_back(innerExpr);
                inner = false;
                continue;
            }
            innerExpr += nestedExpr[i];
            continue;
        }
        if (i > 0 && nestedExpr[i] == '(') {
            inner = true;
            innerExpr += nestedExpr[i];
            pieces.push_back(temp);
            temp = "";
            continue;
        }
        temp += nestedExpr[i];
    }
    pieces.push_back(temp);
    for (auto item : pieces) {
        cout << "Item: " << item << endl;
    }
    return ""; // once pieces[1] is evaluated, the vector can be joined and returned
}

bool checkForNestedParenthesis(string expr)
{
    bool first = false;
    for (char c : expr) {
        if (first) {
            if (c == '(') {
                return true;
            }
        }
        if (c == '(') {
            first = true;
        }
    }
    return false;
}

vector<string> extractExpressionsInParenthesis(string expr)
{
    bool inExpr = false;
    string temp;
    vector<string> result;
    size_t count = 0;
    for (char c : expr) {
        if (c == '(') {
            inExpr = true;
            count++;
        }
        if (inExpr) {
            temp += c;
        }
        if (c == ')') {
            count--;
            if (count == 0) {
                result.push_back(temp);
                temp = "";
            }
        }
        if (c == ')' && count == 0) {
            inExpr = false;
        }
    }
    return result;
}

vector<string> orderOperationsInExpression(string expr)
{
    vector<string> result;
    

}

double evaluateExpression(Number n1, Number n2, string op)
{
    double num1;
    double num2;
    double result;
    if (holds_alternative<int>(n1)) 
        num1 = (double)get<int>(n1);
    else 
        num1 = get<double>(n1);
    if (holds_alternative<int>(n2)) 
        num2 = (double)get<int>(n2);
    else 
        num2 = get<double>(n2);

    if (op.size() > 1) {
        result = pow(num1, num2);
        return result;
    }
    switch (op[0]) {
    case '+':
        result = num1 + num2;
        break;
    case '-':
        result = num1 - num2;
        break;
    case '*':
        result = num1 * num2;
        break;
    case '/':
        if (num2 != 0) 
            result = num1 + num2;
        else 
            result = 0;
        break;
    }
    return result;
}