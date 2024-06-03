#include "lexer.hpp" // iostream, fstream
#include "variables.hpp" // unordered_map, variant
#include "parser.hpp" // vector
#include "arithmetic.hpp" // variant

using namespace std;

int main() 
{
    Variables vars;
    Parser p(vars);
    string file = readFile("../../../test.pr"); // eventually use command line args to provide filename
    vector<string> lines = splitIntoLines(file);
    for (string line : lines) {
        line = removeComment(line);
        vector<string> tokens = tokenizeLine(line);
        // This will take a full rewrite of the lexing logic.
        // Start a branch and get planning.
        p.serveKeywordToken(tokens, vars);
    }
}
