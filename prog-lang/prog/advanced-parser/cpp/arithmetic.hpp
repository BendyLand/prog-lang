#include <variant>

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

using Number = std::variant<int, double>;

double evaluateExpression(Number n1, Number n2, std::string op);
std::vector<std::string> extractExpressionsInParenthesis(std::string expr);
bool checkForNestedParenthesis(std::string expr);
std::string reduceInnerExpression(std::string nestedExpr);

#endif