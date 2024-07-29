#include "logging.hpp" // "utils.hpp" -> "symbols.hpp" ->
                       // iostream, unordered_map, variant; string, fstream, vector; <boost/regex.hpp>
#include "symbols.hpp"
std::vector<std::string> extract_inner_str_variables(std::string text)
{
    std::vector<std::string> result;
    boost::regex pat("\\$\\{(.*?)\\}");
    if (boost::regex_search(text, pat, boost::match_default)) {
        boost::sregex_iterator iter(text.begin(), text.end(), pat);
        boost::sregex_iterator end;
        while (iter != end) {
            boost::smatch m = *iter;
            for (size_t i = 0; i < m.size()/2; i++) {
                std::string item = m[1].str();
                if (contains(item, "${")) continue;
                result.push_back(item);
            }
            iter++;
        }
    }
    return result;
}

std::string extract_text_from_string(std::string original)
{
    std::string result = original;
    boost::regex pat("\"(.*)\"");
    boost::smatch m;
    if (boost::regex_search(original, m, pat)) {
        result = m[1];
    }
    return result;
}

bool contains_inner_variables(std::string text)
{
    boost::regex pat("\\$\\{(.*)\\}");
    return boost::regex_search(text, pat, boost::match_extra);
}

std::string remove_first_token(std::string line)
{
    size_t i = line.find_first_of(" ");
    return line.substr(i+1);
}

bool contains_multiple_args(std::string text)
{
    size_t dQuotes = 0;
    for (size_t i = 0; i < text.size(); i++) {
        if (text[i] == '\"') {
            dQuotes++;
            continue;
        }
        if (dQuotes >= 2 && dQuotes % 2 == 0 && text[i] == ',') return true;
    }
    return false;
}

std::string insert_inner_variables(std::string original, std::vector<std::string> found_vars, SymbolTable vars)
{
    std::vector<std::string> var_values;
    for (std::string name : found_vars) {
        std::optional<AnyType> val_ = vars.get_val(name);
        AnyType val;
        if (val_.has_value()) {
            val = val_.value();
        }
        else {
            exit(EXIT_FAILURE);
        }
        std::string val_str = any_to_string(val);
        var_values.push_back(val_str);
    }
    size_t current = 0;
    size_t x = 0;
    while (original.find("${", current) != std::string::npos) {
        size_t idx = original.find("${", current);
        size_t len = original.find("}") - idx + 1;
        original = original.replace(idx, len, var_values[x]);
        current = idx+1;
        x++;
    }
    return original;
}

void execute_print(std::string text, SymbolTable saved_vars)
{
    bool has_escape_char = contains(text, "\\");
    if (contains_inner_variables(text)) {
        std::vector<std::string> vars = extract_inner_str_variables(text);
        std::string line = extract_text_from_string(text);
        if (!saved_vars.contains_all(vars)) {
            std::cerr << "Attempt to print unknown variable." << std::endl;
            exit(1);
        }
        line = insert_inner_variables(line, vars, saved_vars);
        if (has_escape_char) {
            line = handle_escape_chars(line);
        }
        if (text.starts_with("print")) {
            if (contains_multiple_args(line)) {
                std::cout << "print multiple args: " << line << std::endl;
            }
            else {
                std::cout << line;
            }
        }
        else {
            if (contains_multiple_args(line)) {
                std::cout << "puts multiple args: " << line << std::endl;
            }
            else {
                std::cout << line << std::endl;
            }
        }
    }
    else {
        if (text.starts_with("print")) {
            std::string argStr = remove_first_token(text);
            if (contains_multiple_args(argStr)) {
                std::cout << "print multiple args: " << argStr << std::endl;
            }
            else {
                if (contains(argStr, "\"")) {
                    std::string text = extract_text_from_string(argStr);
                    if (has_escape_char) {
                        text = handle_escape_chars(text);
                    }
                    std::cout << text;
                }
                else {
                    std::cout << "Printing variable: " << argStr << std::endl;
                }
            }
        }
        else {
            std::string argStr = remove_first_token(text);
            if (contains_multiple_args(argStr)) {
                std::cout << "puts multiple args: " << argStr << std::endl;
            }
            else {
                if (contains(argStr, "\"")) {
                    std::string text = extract_text_from_string(argStr);
                    if (has_escape_char) {
                        text = handle_escape_chars(text);
                    }
                    std::cout << text << std::endl;
                }
                else {
                    std::cout << "Printing variable with newline: " << argStr << std::endl;
                }
            }
        }
    }
}

std::string handle_escape_chars(std::string text)
{
    std::string result;
    std::vector<std::string> valid_escapes = {"\\r", "\\n", "\\t", "\\\\", "\\\""};
    if (contains_any(text, valid_escapes)) {
        while (contains_any(text, valid_escapes)) {
            if (contains(text, "\\r")) {
                size_t idx = text.find("\\r");
                result = text.replace(idx, 2, "\r");
            }
            if (contains(text, "\\n")) {
                size_t idx = text.find("\\n");
                result = text.replace(idx, 2, "\n");
            }
            if (contains(text, "\\t")) {
                size_t idx = text.find("\\t");
                result = text.replace(idx, 2, "\t");
            }
            if (contains(text, "\\\\")) {
                size_t idx = text.find("\\\\");
                result = text.replace(idx, 2, "\\");
            }
            if (contains(text, "\\\"")) {
                size_t idx = text.find("\\\"");
                result = text.replace(idx, 2, "\"");
            }
        }
    }
    return result;
}

/*
* Complications:
* - Variables may be passed before they exist.
*     - Panic.
* - DQuotes may be unmatched.
*     - Panic.
// - Strings may contain escaped characters.
//     - Handle per case.
// - Escaped characters (currently) include: \", \r, \n, \t, \\.
*/
