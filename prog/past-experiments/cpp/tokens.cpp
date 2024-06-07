#include "tokens.hpp"

std::ostream& operator<<(std::ostream& os, const Token& t) 
{
    switch (t.getType()) {
    case Tokens::LET:
        os << "LET";
        break;
    case Tokens::IDENTIFIER:
        os << t.getValue();
        break;
    case Tokens::EQUAL_SIGN:
        os << "=";
        break;
    case Tokens::VALUE:
        os << t.getValue();
        break;
    }
    return os;
}

// Object constructors.
Token::Token(Tokens type) : type(type) {}
Token::Token(Tokens type, const std::string &value) : type(type), value(value) {}

// Getters for private fields.
Tokens Token::getType() const
{
    return type;
}

Value Token::getValue() const 
{
    return value;
}