#include "lexer.hpp" // iostream, fstream
#include "variables.hpp" // unordered_map, variant
#include "parser.hpp" // vector
#include "arithmetic.hpp" // variant
#include "utils.hpp"

using namespace std;

int main() 
{
    Variables vars;
    Parser p(vars);
    string file = readFile("../../../test.pr"); // eventually use command line args to provide filename
    vector<string> lines = splitIntoLines(file);
    for (string line : lines) {
        line = removeComment(line);
        ltrim(line);
        rtrim(line);
        cout << "Line: " << line << endl;
    }
}
