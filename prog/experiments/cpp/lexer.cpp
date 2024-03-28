#include <iostream>
#include <fstream>
#include <vector>
#include "lexer.h"

using namespace std;

Lexer::Lexer(string text) :
    _text(text),
    _current(text.empty() ? '\0' : text[0]), 
    _index(0), _next(text.size() > 1 ? text[1] : '\0'),
    _size(text.size()) 
{}

vector<string> splitIntoLines(string file)
{
    vector<string> lines;
    string line = "";
    for (char c : file) {
        line += c;
        if (c == '\n') {
            lines.push_back(line);
            line = "";
        }
    }
    return lines;
}

void Lexer::increment() 
{
    if (this->_index < this->_size - 1) {
        this->_index++;
        this->_current = _text[this->_index];
        this->_next = _text[this->_index+1];
    }
}
char Lexer::getCurrent() { return _current; }
char Lexer::getNext() { return _next; }
int Lexer::getIndex() { return _index; }
int Lexer::size() { return _size; }

string readFile(string path) 
{
    ifstream file;
    string line;
    string result = "";
    file.open(path);
    if (file.is_open()) {
        while (getline(file, line)) 
            result += line + "\n";
        file.close();
    }
    else 
        cout << "Unable to open file." << endl;
    return result;
}