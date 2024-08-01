#include <boost/regex.hpp>
#include "conditional.hpp"
#include "exprtk.hpp"

std::string extract_conditional_expr(std::string line)
{
    size_t start = 0;
    if (contains(line, "elif")) {
        start = line.find("elif") + 4;
    }
    else if (contains(line, "if")) {
        start = line.find("if") + 2;
    }
    size_t len = 0;
    if (contains(line, "{")) {
        len = line.find("{") - start;
    }
    else {
        len = line.size();
    }
    std::string result = line.substr(start, len);
    return strip(result);
}

std::vector<std::string> extract_boolean_expr_variables(std::string text)
{
    std::vector<std::string> result;
    boost::regex pat("([a-zA-Z_]+)");
    if (boost::regex_search(text, pat, boost::match_default)) {
        boost::sregex_iterator iter(text.begin(), text.end(), pat);
        boost::sregex_iterator end;
        while (iter != end) {
            boost::smatch m = *iter;
            for (size_t i = 0; i < m.size()/2; i++) {
                std::string item = m[1].str();
                result.push_back(item);
            }
            iter++;
        }
    }
    return result;
}

bool evaluate_conditional(std::string expr, SymbolTable symbols)
{
    exprtk::symbol_table<double> symbol_table;
    exprtk::expression<double> expression;
    exprtk::parser<double> parser;
    std::vector<std::string> variables = extract_boolean_expr_variables(expr);
    for (std::string var : variables) {
        std::optional<AnyType> value = symbols.get_val(var);
        if (value.has_value()) {
            if (std::holds_alternative<double>(value.value())) {
                AnyType anyTemp = value.value();
                double temp = std::get<double>(anyTemp);
                symbol_table.add_variable(var, temp);
            }
            else if (std::holds_alternative<int>(value.value())) {
                //! when given two of the same type of variable, the second value will overwrite the first.
                AnyType anyTemp = value.value();
                int intTemp = std::get<int>(anyTemp);
                double temp = static_cast<double>(intTemp);
                symbol_table.add_constant(var, temp); //! changed to add_constant for now to fix.
            }
            else {
                std::cout << "I'll handle these later." << std::endl;
            }
        }
        else {
            std::cout << "Variable has no value" << std::endl;
        }
    }
    expression.register_symbol_table(symbol_table);
    if (!parser.compile(expr, expression)) {
        std::cerr << "Error evaluating: " << parser.error() << std::endl;
        return false;
    }
    double result = expression.value();
    return result != 0;
}
