#include <unistd.h>
#include "lexer.hpp" // "utils.hpp" -> iostream, fstream, string, vector

using namespace std;

int main()
{
    string file = readFile("../../../test.pr");
    cout << "Before: " << endl << file << endl;
    file = prepareFile(file);
    cout << "After: " << endl << file << endl;
    // sleep(10);
    return 0;
}
