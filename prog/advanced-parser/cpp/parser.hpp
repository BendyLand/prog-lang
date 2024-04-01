#include <vector>
#include <sstream>
#include "lexer.hpp"
#include "variables.hpp"

class Parser {
public:
    Parser();
    void serveKeywordToken(std::vector<std::string>);
};

void parseVariableLine(std::vector<std::string>);
