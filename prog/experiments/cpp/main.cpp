#include <iostream>
#include <vector>
#include "lexer.hpp"

using namespace std;

int main() 
{
    string file = readFile("../../../test.pr");
    vector<string> lines = splitIntoLines(file);
    for (string line : lines) {
        line = removeComment(line);
        vector<string> tokens = tokenizeLine(line);
        for (string token : tokens) {
            cout << token << endl;
        }
    }
}
