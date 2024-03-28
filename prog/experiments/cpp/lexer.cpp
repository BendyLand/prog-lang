#include <iostream>
#include <fstream>
#include <vector>
#include "lexer.hpp"

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
        if (l.getCurrent() == '/' && l.getNext() == '/')
            isComment = true;
        if (!isComment)
            newStr += l.getCurrent();
        l.increment();
    }
    return newStr;
}

string trimLeadingWhitespace(string line) 
{
    string result = "";
    size_t i = line.find_first_not_of(' ');
    if (i != string::npos) {
        while (i < line.size()) {
            result += line[i];
            i++;
        }
    }
    return result;
}

vector<string> tokenizeLine(string line)
{
    Lexer l(line);
    vector<string> result;
    if (line.find("\"") != string::npos) 
        tokenizeStringLine(l, result, line);
    else 
        tokenizeNonStringLine(l, result, line);
    
    return result;
}

void tokenizeNonStringLine(Lexer l, vector<string>& result, string line)
{
    string token = "";
    while (true) {
        if (l.getCurrent() == ' ') {
            token = trimLeadingWhitespace(token);
            result.push_back(token);
            token = "";
        }
        token += l.getCurrent();
        if (l.getNext() == '\n' || l.getIndex() >= l.size()) 
            goto end;
        l.increment();
    }
    end:
    token = trimLeadingWhitespace(token);
    result.push_back(token);
}

void tokenizeStringLine(Lexer l, vector<string>& result, string line) 
{
    string embeddedStr = tokenizeString(line);
    string token = "";
    while (true) {
        if (l.getCurrent() == ' ') {
            token = trimLeadingWhitespace(token);
            result.push_back(token);
            token = "";
        }
        token += l.getCurrent();
        if (l.getCurrent() == '"') {
            goto end;
        }
        l.increment();
    }
    end:
    result.push_back(embeddedStr);
}

string tokenizeString(string line) 
{
    string result = "";
    Lexer l(line);
    bool inString = false;
    while (l.getIndex() < l.size()-1) {
        if (l.getCurrent() == '"') {
            if (inString) 
                result += l.getCurrent();
            inString = true;
            l.increment();
            continue;
        }
        if (inString) {
            if (l.getCurrent() == '\\' && l.getNext() == 'n') {
                result += '\n';
                for (int i = 0; i < 2; i++)
                    l.increment();
                continue;
            }
            if (l.getNext() == '"' && l.getCurrent() != '\\') {
                result += l.getCurrent();
                goto end;
            }
            result += l.getCurrent();
        }
        l.increment();
    }
    end:
    return result;
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