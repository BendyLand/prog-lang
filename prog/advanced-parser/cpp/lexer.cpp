#include <vector>
#include "utils.hpp" // includes <algorithm>, <cctype>, <locale>
#include "lexer.hpp" // includes <iostream>, <fstream>

using namespace std;

Lexer::Lexer(string text) :
    _text(text),
    _current(text.empty() ? '\0' : text[0]), 
    _index(0), _next(text.size() > 1 ? text[1] : '\0'),
    _size(text.size()) 
{}

vector<string> removeEmptyTokens(vector<string> tokens)
{
    vector<string> result;
    for (string token : tokens) {
        if (!token.empty()) 
            result.push_back(token);
    }
    return result;
}

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

vector<string> tokenizeLine(string line)
{
    Lexer l(line);
    vector<string> result;
    if (line.find("\"") != string::npos) 
        result = tokenizeStringLine(l, line);
    else 
        result = tokenizeNonStringLine(l, line);
    
    return result;
}

vector<string> tokenizeNonStringLine(Lexer l, string line)
{
    vector<string> result;
    string token = "";
    while (true) {
        if (l.getCurrent() == ' ') {
            ltrim(token);
            result.push_back(token);
            token = "";
        }
        token += l.getCurrent();
        if (l.getNext() == '\n' || l.getIndex() >= l.size()) 
            goto end;
        l.increment();
    }
    end:
    ltrim(token);
    result.push_back(token);
    return result;
}

vector<string> tokenizeStringLine(Lexer l, string line) 
{
    vector<string> result;
    string embeddedStr = tokenizeString(line);
    string token = "";
    while (true) {
        if (l.getCurrent() == ' ') {
            ltrim(token);
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
    return result;
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