#include <iostream>
#include <vector>
#include "lexer.hpp"
#include "variables.hpp"
#include "parser.hpp"
#include "arithmetic.hpp"

using namespace std;

int main() 
{
    Variables vars;
    Parser p(vars);
    string file = readFile("../../../test.pr");
    vector<string> lines = splitIntoLines(file);
    for (string line : lines) {
        line = removeComment(line);
        vector<string> tokens = tokenizeLine(line);
        p.serveKeywordToken(tokens, vars);
    }
    // string file = readFile("../../../arithmetic-examples.txt");
    // vector<string> lines = splitIntoLines(file);
    // for (auto line : lines) {
    //     vector<string> temp = extractExpressionsInParenthesis(line);
    //     cout << "New line:" << endl;
    //     for (auto item : temp) {
    //         cout << "Item: " << item << endl;
    //         bool nested = checkForNestedParenthesis(item);
    //         if (nested) {
    //             reduceInnerExpression(item);
    //         }
    //     }
    // }
}
