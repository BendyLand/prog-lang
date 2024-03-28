#include <iostream>
#include <fstream>

using namespace std;

class Lexer 
{
public:
    Lexer(string text) 
    {
        this->_text = text;
        this->_current = text[0];
        this->_index = 0;
        if (text.size() > 1) 
            this->_next = text[1];
        else
            this->_next = '\0';
    }
    void increment() 
    {
        this->_index++;
        this->_current = _text[this->_index];
        this->_next = _text[this->_index+1];
    }
    char getCurrent() { return _current; }
    char getNext() { return _next; }
    int getIndex() { return _index; }

private:
    string _text;
    char _current;
    char _next;
    int _index;
};

string readFile(string);

int main() 
{
    string file = readFile("../../../test.pr");
    cout << file << endl;
}

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