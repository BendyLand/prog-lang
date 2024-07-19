#include "utils.hpp" // "symbols.hpp" -> iostream, unordered_map, variant; string, fstream, vector

using namespace std;

string readFile(string path)
{
    ifstream file(path);
    string result;
    char c;
    while (file) {
        c = file.get();
        if (c > 0) {
            result += c;
        }
    }
    file.close();
    return result;
}

vector<string> split(string text, string delim)
{
    size_t pos = 0;
    string token;
    vector<string> result;
    while ((pos = text.find(delim)) != string::npos) {
        token = text.substr(0, pos);
        result.push_back(token);
        text.erase(0, pos + delim.size());
    }
    if (text.size() > 0) {
        result.push_back(text);
    }
    return result;
}

bool containsEmbeddedString(string src)
{
    size_t first = src.find_first_of("\"");
    size_t last = src.find_last_of("\"");
    return (first != last) && (first != string::npos);
}

bool contains(string haystack, string needle)
{
    return haystack.find(needle) != string::npos;
}

string lstrip(string original)
{
    string result = "";
    for (char c : original) {
        if (result.size() == 0 && isspace(c)) {
            continue; 
        }
        result += c;
    }
    return result;
}

string reverse(string original)
{
    string result = "";
    for (int i = original.size()-1; i >= 0; i--) {
        result += original[i];
    }
    return result;
}

string rstrip(string original)
{
    if (!original.ends_with(" ")) {
        return original;
    }
    string temp = reverse(original);
    temp = lstrip(temp);
    string result = reverse(temp);
    return result;
}

string strip(string original)
{
    string result = original;
    result = rstrip(original);
    return lstrip(result);
}

string removeInnerWhitespace(string original)
{
    string result = "";
    for (char c : original) {
        if (!isspace(c)) {
            result += c;
        }
    }
    return result;
}

size_t count(string str, char c)
{
    size_t result = 0;
    for (char ch : str) {
        if (c == ch) result++;
    }
    return result;
}

string getVarType(AnyType var)
{
    string result = "";
    if (holds_alternative<int>(var)) {
        result = "int";
    }
    else if (holds_alternative<double>(var)) {
        result = "double";
    }
    else if (holds_alternative<char>(var)) {
        result = "char";
    }
    else if (holds_alternative<string>(var)) {
        result = "str";
    }
    else if (holds_alternative<bool>(var)) {
        result = "bool";
    }
    return result;
}
