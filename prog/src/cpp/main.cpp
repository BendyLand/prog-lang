#include <unistd.h>
#include "lexer.hpp" 
/* 
"lexer.hpp" includes: 
"logging.hpp"     -> "utils.hpp", <boost/regex.hpp>
    "utils.hpp"   -> "symbols.hpp", iostream, string, fstream, vector
    "symbols.hpp" -> iostream, unordered_map, variant
"arithmetic.hpp"  -> "exprtk.hpp"
"conditional.hpp" -> "utils.hpp", "exprtk.hpp", <boost/regex.hpp>
*/

int main(int argc, char** argv)
{
    std::string path = "../../../test.pr";
    if (argc > 1) {
        path = std::string(argv[1]);
    }
    std::string file = read_file(path);
    Variables global_vars;
    SymbolTable symbols(global_vars);
    file = prepare_file(file);
    std::vector<std::string> lines = split(file, "\n");
    for (auto item : lines) {
        std::cout << "Item: " << item << std::endl;
    }
    // sleep(10);
    return 0;
}

//todo: Start new approach to tokenizing the normalized lines
