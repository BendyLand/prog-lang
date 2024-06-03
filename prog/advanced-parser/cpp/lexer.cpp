#include <vector>
#include "utils.hpp" // includes <algorithm>, <cctype>, <locale>
#include "lexer.hpp" // includes <iostream>, <fstream>, "tokens.hpp"/<string>

using namespace std;

Lexer::Lexer(string text) :
    _text(text),
    _current(text.empty() ? '\0' : text[0]), 
    _index(0), _next(text.size() > 1 ? text[1] : '\0'),
    _size(text.size()) 
{}

string removeComment(string line) 
{
    Lexer l (line);
    string newStr = "";
    bool isComment = false;
    while (l.getNext() == '\n' || l.getIndex() < l.size()-1) {
        if (l.getCurrent() == '#')
            isComment = true;
        if (!isComment)
            newStr += l.getCurrent();
        l.increment();
    }
    return newStr;
}

vector<Token> tokenizeLine(string line)
{
    Lexer l(line);
    vector<Token> result;
    if (line.find("\"") != string::npos) 
        result = tokenizeStringLine(l, line);
    else 
        result = tokenizeNonStringLine(l, line);
    
    return result;
}

vector<Token> tokenizeNonStringLine(Lexer l, string line)
{
    vector<Token> result;
    return result;
}

vector<Token> tokenizeStringLine(Lexer l, string line) 
{
    vector<Token> result;
    return result;
}

Token tokenizeString(string line) 
{
    return Token(Tokens::LET);
}

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
    if (this->_index < this->_size) {
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