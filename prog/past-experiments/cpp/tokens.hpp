#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>
#include "variables.hpp"

using Value = std::variant<int, double, char, std::string, bool>;

enum class Tokens {
    LET,
    IDENTIFIER,
    EQUAL_SIGN,
    VALUE,
    FOR,
    IF,
    ELIF,
    ELSE
};

class Token 
{
public:
    Token(Tokens);
    Token(Tokens, const std::string&);
    Tokens getType() const;
    Value getValue() const;

private:
    Tokens type;
    Value value;
};

std::ostream& operator<<(std::ostream& os, const Token& t);

#endif
