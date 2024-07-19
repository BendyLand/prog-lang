#include <unistd.h>
#include "lexer.hpp" // "utils.hpp" -> iostream, fstream, string, vector
#include "logging.hpp" // iostream, <boost/regex.hpp>
#include "symbols.hpp" // iostream, variant, unordered_map

using namespace std;

int main()
{
    string file = readFile("../../test.pr");
    Variables vars;
    SymbolTable symbols(vars);
    file = prepareFile(file);
    vector<string> lines = split(file, "\n");
    for (string line : lines) {
        if (line.starts_with("print") || line.starts_with("puts")) {
            executePrint(line);
        }
        else if (line.starts_with("let")) {
            //todo: create extractVarName(), extractVarValue(), then save them to symbols.
            cout << "Saving variable... (nothing happens yet)" << endl;
            string name = extractVarName(line);
            AnyType value = extractVarValue(line);
        }
        else {
            cout << "Line: " << line << endl;
        }
    }
    // sleep(10);
    return 0;
}
