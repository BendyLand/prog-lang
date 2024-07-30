#include <unistd.h>
#include "lexer.hpp" // "utils.hpp" -> iostream, fstream, string, vector
#include "logging.hpp" // iostream, <boost/regex.hpp>
#include "symbols.hpp" // iostream, variant, unordered_map

int main()
{
    std::string file = read_file("../../test.pr");
    Variables global_vars;
    SymbolTable symbols(global_vars);
    file = prepare_file(file);
    std::vector<std::string> lines = split(file, "\n");
    for (std::string line : lines) {
        if (line.starts_with("print") || line.starts_with("puts")) {
            execute_print(line, symbols);
        }
        else if (line.starts_with("let")) {
            std::string name = extract_var_name(line);
            AnyType value = extract_var_value(line);
            symbols.add_var(name, value);
        }
        else {
            if (lstrip(line).starts_with("if")) {
                std::cout << "Handle if statement: " << line << std::endl;
            }
            else if (line.find("elif") != std::string::npos) {
                std::cout << "Handle elif: " << line << std::endl;
            }
            else if (line.find("else") != std::string::npos) {
                std::cout << "Handle else: " << line << std::endl;
            }
            else if (lstrip(line).starts_with("for")) {
                std::cout << "Handle loop: " << line << std::endl;
            }
            else {
                std::cout << "Unknown line: " << line << std::endl;
            }
        }
    }
    std::cout << "\n\nDisplaying current variables:" << std::endl;
    symbols.display_vars();
    // sleep(10);
    return 0;
}
