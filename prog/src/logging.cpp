#include "logging.hpp" // "utils.hpp" -> "symbols.hpp" ->
                       // iostream, unordered_map, variant; string, fstream, vector; <boost/regex.hpp>

std::vector<std::string> extract_inner_str_variables(std::string text)
{
    std::vector<std::string> result;
    boost::regex pat("\\$\\{(.*?)\\}");
    if (boost::regex_search(text, pat, boost::match_default)) {
        boost::sregex_iterator iter(text.begin(), text.end(), pat);
        boost::sregex_iterator end;
        while (iter != end) {
            boost::smatch m = *iter;
            for (size_t i = 0; i < m.size(); i++) {
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

void execute_print(std::string text)
{
    bool has_escape_char = false;
    if (contains(text, "\\")) has_escape_char = true;
    if (contains_inner_variables(text)) {
        std::vector<std::string> vars = extract_inner_str_variables(text);
        vars = dedup(vars);
        std::string line = remove_first_token(text);
        std::cout << "log contains variable: " << line << std::endl;
        for (std::string var : vars) {
            std::cout << "\tVar: " << var << std::endl;
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
