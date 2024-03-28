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

#endif