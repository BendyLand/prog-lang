#include <unistd.h>
#include "lexer.hpp" // "utils.hpp" -> iostream, fstream, string, vector
#include "logging.hpp" // iostream, <boost/regex.hpp>
#include "symbols.hpp" // iostream, variant, unordered_map
#include "conditional.hpp"

void mainLoop(std::vector<std::string>&, SymbolTable&);

int main(int argc, char** argv)
{
    std::string path = "../../test.pr";
    if (argc > 1) {
        path = std::string(argv[1]);
    }
    std::string file = read_file(path);
    Variables global_vars;
    SymbolTable symbols(global_vars);
    file = prepare_file(file);
    std::vector<std::string> lines = split(file, "\n");
    mainLoop(lines, symbols);
    // sleep(10);
    return 0;
}

void mainLoop(std::vector<std::string>& lines, SymbolTable& symbols)
{
    // if for some reason these go negative, size_t wrapping breaks the program
    int num_if_scopes = 0;
    int num_elif_scopes = 0;
    int num_else_scopes = 0;
    int num_for_scopes = 0;
    char last_local_scope = 'g';
    char scope_storage = last_local_scope;
    bool if_skip = false;
    bool elif_skip = false;
    bool else_skip = false;
    std::string current_attempt = "";
    for (std::string line : lines) {
        if (if_skip || elif_skip || else_skip) {
            if (contains(line, "}") && strip(line).size() < 2) {
                //todo: place logic here to keep track of scope
                if (if_skip) if_skip = false;
                else if (elif_skip) elif_skip = false;
                else if (else_skip) else_skip = false; 
                scope_storage = last_local_scope;
                last_local_scope = 'g';
            }
            continue;
        }
        if (line.starts_with("print") || line.starts_with("puts")) {
            //! strings with more than two vars interpolated are cut short.
            std::cout << "Here" << std::endl;
            execute_print(line, symbols);
        }
        else if (line.starts_with("let")) {
            std::string name = extract_var_name(line);
            AnyType value = extract_var_value(line);
            switch (last_local_scope) {
            case 'i':
                symbols.add_l_var(name, value, "if_"+std::to_string(num_if_scopes-1));
                break;
            case 'l':
                symbols.add_l_var(name, value, "elif_"+std::to_string(num_elif_scopes-1));
                break;
            case 's':
                symbols.add_l_var(name, value, "else_"+std::to_string(num_else_scopes-1));
                break;
            case 'f':
                symbols.add_l_var(name, value, "for_"+std::to_string(num_for_scopes-1));
                break;
            default:
                symbols.add_var(name, value);
                break;
            }
        }
        else {
            if (lstrip(line).starts_with("if")) {
                std::string expr = extract_conditional_expr(line);
                bool condition_result = evaluate_conditional(expr, symbols);
                if (condition_result) {
                    symbols.new_l_vars("if_"+std::to_string(num_if_scopes));
                    scope_storage = last_local_scope;
                    last_local_scope = 'i';
                    num_if_scopes++;
                }
                else {
                    if_skip = true;
                    current_attempt = "elif";
                }
            }
            else if (contains(line, "elif")) {
                if (current_attempt == "elif") {
                    std::string expr = extract_conditional_expr(line);
                    bool condition_result = evaluate_conditional(expr, symbols);
                    if (condition_result) {
                        if (contains(line, "}")) num_if_scopes--;
                        symbols.new_l_vars("elif_"+std::to_string(num_elif_scopes));
                        scope_storage = last_local_scope;
                        last_local_scope = 'l';
                        num_elif_scopes++;
                        if_skip = false;
                    }
                    else {
                        if_skip = false;
                        elif_skip = true;
                        else_skip = false;
                        current_attempt = "else";
                    }
                }
                else {
                    elif_skip = true;
                    else_skip = true;
                }
            }
            else if (contains(line, "else")) {
                if (current_attempt == "else") {
                    if (contains(line, "}")) num_elif_scopes--;
                    symbols.new_l_vars("else_"+std::to_string(num_else_scopes));
                    scope_storage = last_local_scope;
                    last_local_scope = 's';
                    num_else_scopes++;
                    if_skip = false;
                    elif_skip = false;
                }
                else {
                    else_skip = true;
                }
            }
            else if (lstrip(line).starts_with("for")) {
                std::cout << "Handle loop: " << line << std::endl;
                symbols.new_l_vars("for_"+std::to_string(num_for_scopes));
                scope_storage = last_local_scope;
                last_local_scope = 'f';
                num_for_scopes++;
            }
            else {
                if (contains(line, "}")) {
                    switch (last_local_scope) {
                    case 'i':
                        symbols.pop_l_vars("if_"+std::to_string(num_if_scopes));
                        num_if_scopes--;
                        break;
                    case 'l':
                        symbols.pop_l_vars("elif_"+std::to_string(num_elif_scopes));
                        num_elif_scopes--;
                        break;
                    case 's':
                        symbols.pop_l_vars("else_"+std::to_string(num_else_scopes));
                        num_else_scopes--;
                        break;
                    case 'f':
                        symbols.pop_l_vars("for_"+std::to_string(num_for_scopes));
                        num_for_scopes--;
                        break;
                    }
                }
                last_local_scope = scope_storage;
            }
        }
    }
    symbols.display_g_vars();
}
