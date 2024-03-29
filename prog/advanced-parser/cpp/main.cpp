#include <iostream>
#include <vector>
#include "lexer.hpp"
#include "variables.hpp"
#include "parser.hpp"

using namespace std;

void serveKeywordToken(vector<string>);

int main() 
{
    Variables vars;
    Parser p;
    string file = readFile("../../../test.pr");
    vector<string> lines = splitIntoLines(file);
    for (string line : lines) {
        line = removeComment(line);
        vector<string> tokens = tokenizeLine(line);
        p.serveKeywordToken(tokens);
    }
}
