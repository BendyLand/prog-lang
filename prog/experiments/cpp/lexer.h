#include <iostream>
#include <fstream>

#ifndef LEXER_H
#define LEXER_H

class Lexer
{
public:
    Lexer(std::string text);
    void increment();
    char getCurrent();
    void setCurrent(char);
    void setNext(char);
    char getNext();
    int getIndex();
    int size();

private:
    std::string _text;
    char _current;
    char _next;
    int _index;
    int _size;
};

std::string readFile(std::string);
std::vector<std::string> splitIntoLines(std::string);
std::string tokenizeString(std::string);
std::vector<std::string> tokenizeLine(std::string);
void tokenizeStringLine(Lexer, std::vector<std::string>&, std::string);
void tokenizeNonStringLine(Lexer, std::vector<std::string>&, std::string);
std::string removeComment(std::string);

#endif