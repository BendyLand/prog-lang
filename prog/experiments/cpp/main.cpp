#include <unistd.h>
#include "lexer.hpp" // "utils.hpp" -> iostream, fstream, string, vector
#include "logging.hpp"

using namespace std;

int main()
{
    string file = readFile("../../../test.pr");
    file = prepareFile(file);
    vector<string> lines = strSplit(file, "\n");
    for (string line : lines) {
        if (line.starts_with("print") || line.starts_with("puts")) {
            executePrint(line);
        }
        else {
            cout << "Line: " << line << endl;
        }
    }
    // sleep(10);
    return 0;
}
