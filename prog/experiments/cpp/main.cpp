#include <iostream>
#include <vector>
#include "lexer.h"

using namespace std;

int main() 
{
    string file = readFile("../../../test.pr");
    vector<string> lines = splitIntoLines(file);
    for (string line : lines) {
        cout << line << endl;
    }
}


