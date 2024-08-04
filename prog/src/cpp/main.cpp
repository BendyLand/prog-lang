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
        //todo: multiple elif branches are not handled properly. 
        //todo: conditional evaluation is not accurate when comparing two arithmetic results. 
        //todo: when performing arithmetic on a variable, must insert var value into expression before evaluating. 
        //? restructure loop to identify blocks with current_attempt and add operations to a master list, 
            //? then execute?
        if (if_skip || elif_skip || else_skip) {
            if (contains(line, "}")) {
                if (contains(line, "elif")) goto Elif;
                if (if_skip) if_skip = false;
                else if (elif_skip) elif_skip = false;
                else if (else_skip) else_skip = false; 
                last_local_scope = scope_storage;
                if (contains(line, "else")) {
                    scope_storage = 'g';
                    last_local_scope = 's';
                    num_elif_scopes--;
                }
            }
            continue;
        }
        if (line.starts_with("print") || line.starts_with("puts")) {
            execute_print(line, symbols);
        }
        else if (line.starts_with("let")) {
            std::string name = extract_var_name(line);
            AnyType value = extract_var_value(line, symbols);
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
                Elif:
                if (current_attempt == "elif") {
                    std::string expr = extract_conditional_expr(line);
                    bool condition_result = evaluate_conditional(expr, symbols);
                    if (condition_result) {
                        if (contains(line, "}") && num_if_scopes > 0) num_if_scopes--;
                        symbols.new_l_vars("elif_"+std::to_string(num_elif_scopes));
                        scope_storage = last_local_scope;
                        last_local_scope = 'l';
                        num_elif_scopes++;
                        if_skip = false;
                        // can't make else_skip true here, otherwise will skip correct branch
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
                    if (current_attempt == "elif") {
                        symbols.pop_l_vars("elif_"+std::to_string(num_elif_scopes));
                        num_elif_scopes--;
                    }
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
                    case 's':
                        symbols.pop_l_vars("else_"+std::to_string(num_else_scopes));
                        num_else_scopes--;
                        break;
                    case 'f':
                        symbols.pop_l_vars("for_"+std::to_string(num_for_scopes));
                        num_for_scopes--;
                        break;
                    }
                    last_local_scope = scope_storage;
                }
                if (last_local_scope == scope_storage) last_local_scope = 'g';
            }
        }
    }
    symbols.display_g_vars();
}
