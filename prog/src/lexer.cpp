#include "arithmetic.hpp"
#include "lexer.hpp" // "utils.hpp" -> iostream, string, fstream, vector; "symbols.hpp" -> unordered_map, variant; <boost/regex.hpp>
#include "logging.hpp" // "utils.hpp", <boost/regex.hpp>

std::string prepare_file(std::string file)
{
    file = remove_comments(file);
    file = normalize(file);
    file = remove_empty_lines(file);
    return file;
}

std::string normalize(std::string file)
{
    std::string result = "";
    std::vector<std::string> lines = split(file, "\n");
    for (std::string line : lines) {
        std::string temp = lstrip(line);
        result += temp + "\n";
    }
    return result;
}

std::string remove_comments(std::string file)
{
    std::string result = "";
    std::vector<std::string> lines = split(file, "\n");
    for (std::string line : lines) {
        if (line.find("#") != std::string::npos) {
            size_t comment = line.find("#");
            if (contains_embedded_string(line)) {
                size_t start = line.find_first_of("\"");
                size_t end = line.find_last_of("\"");
                if (comment > start && comment < end) {
                    result += line + "\n";
                    continue; //! currently cannot place comments after strings that contain '#'
                }
            }
            std::string temp = line.substr(0, comment);
            result += temp + "\n";
        }
        else {
            result += line + "\n";
        }
    }
    return result;
}

std::string remove_empty_lines(std::string file)
{
    std::vector<std::string> lines = split(file, "\n");
    std::string result = "";
    for (std::string line : lines) {
        if (line.empty()) {
            continue;
        }
        result += line + "\n";
    }
    return result;
}

bool identify_arithmetic_expression(std::string line)
{
    boost::regex pat(R"(\(?\-?\d+(.\d+)?([\+\-\*/]?\(?\d+(.\d+)?\)?)+)");
    return boost::regex_match(line, pat);
}

std::string extract_var_name(std::string line)
{
    std::vector<std::string> words = split(line, " ");
    std::string name = "";
    if (words.size() > 1) {
        if (words[1] != "mut") {
            name = words[1];
        }
        else {
            name = words[2];
        }
    }
    return name;
}

AnyType parse_val_into_type(std::string val, std::string type)
{
    AnyType result;
    if (type == "int") {
        result = std::stoi(val);
    }
    else if (type == "double") {
        result = std::stod(val);
    }
    else if (type == "char") {
        result = val[1];
    }
    else if (type == "bool") {
        result = (val == "true") ? true : false;
    }
    else if (type == "arithmetic") {
        double temp = reduce_arithmetic_expr(val);
        result = temp;
    }
    else if (type == "variable") {
        //todo: lookup variables
        result = val; //! temporary
    }
    else {
        result = val.substr(1, val.size()-2);
    }
    return result;
}

AnyType extract_var_value(std::string line)
{
    size_t start = line.find("=");
    if (start == std::string::npos) return "";
    std::string resultStr = strip(line.substr(start+1));
    std::string valType = infer_type(resultStr);
    AnyType result = parse_val_into_type(resultStr, valType);
    return result;
}

std::string infer_type(std::string original)
{
    boost::regex doublePat("[0-9]*\\.[0-9]+");
    boost::regex intPat("[0-9]+");
    boost::regex boolPat("true|false");
    boost::regex strPat(R"(\".*\")");
    std::string result;
    if (boost::regex_match(original, doublePat)) {
        result = "double";
    }
    else if (boost::regex_match(original, intPat)) {
        result = "int";
    }
    else if (boost::regex_match(original, boolPat)) {
        result = "bool";
    }
    else if (count(original, '\'') == 2 && original.size() <= 3) {
        result = "char";
    }
    else if (boost::regex_match(original, strPat)) {
        result = "str";
    }
    else {
        original = remove_inner_whitespace(original);
        if (identify_arithmetic_expression(original)) {
            // just in case: R"(\(?\-?\d+(.\d+)?([\+\-\*/]\*?\(?\d+(.\d+)?\)?)+)"
            result = "arithmetic";
        }
        else {
            result = "variable";
        }
    }
    return result;
}
