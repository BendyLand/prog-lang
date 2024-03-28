#include <iostream>
#include <vector>
#include "lexer.hpp"

using namespace std;

void serveKeywordToken(vector<string>);

int main() 
{
    string file = readFile("../../../test.pr");
    vector<string> lines = splitIntoLines(file);
    for (string line : lines) {
        line = removeComment(line);
        vector<string> tokens = tokenizeLine(line);
        serveKeywordToken(tokens);
    }
}

void serveKeywordToken(vector<string> tokens) 
{
    tokens = removeEmptyTokens(tokens);
    if (tokens[0].compare("print") == 0)
        cout << tokens[1];
    else if (tokens[0].compare("puts") == 0) 
        cout << tokens[1] << endl;
    else if (tokens[0].compare("let") == 0) 
        cout << "I'm in the `let` branch" << endl;
    else if (tokens[0].compare("if") == 0)
        cout << "I'm in the `if` branch" << endl;
    else if (tokens[0].compare("for") == 0)
        cout << "I'm in the `for` branch" << endl;
    else
        cout << "This line doesn't have a keyword" << endl;
}
