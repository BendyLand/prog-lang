#include "arithmetic.hpp" 

double reduce_arithmetic_expr(std::string expr)
{
    exprtk::parser<double> parser;
    exprtk::expression<double> expression;
    exprtk::symbol_table<double> symbol_table;
    expression.register_symbol_table(symbol_table);
    if (!parser.compile(expr, expression)) {
        std::cerr << "Error: " << parser.error() << std::endl;
        return 0.0;
    }
    return expression.value();
}
