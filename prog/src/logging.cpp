#include "logging.hpp" // "utils.hpp" -> "symbols.hpp" -> 
                       // iostream, unordered_map, variant; string, fstream, vector; <boost/regex.hpp>

using namespace std;

vector<string> extractInnerStrVariables(string text)
{
    vector<string> result;
    boost::regex pat("\\$\\{(.*?)\\}");
    if (boost::regex_search(text, pat, boost::match_default)) {
        boost::sregex_iterator iter(text.begin(), text.end(), pat);
        boost::sregex_iterator end;
        while (iter != end) {
            boost::smatch m = *iter;
            for (size_t i = 0; i < m.size(); i++) {
                string item = m[1].str();
                if (contains(item, "${")) continue;
                result.push_back(item);
            }
            iter++;
        }
    }
    return result;
}

string extractTextFromString(string original)
{
    string result = original;
    boost::regex pat("\"(.*)\"");
    boost::smatch m;
    if (boost::regex_search(original, m, pat)) {
        result = m[1];
    }
    return result;
}

bool containsInnerVariables(string text)
{
    boost::regex pat("\\$\\{(.*)\\}");
    return boost::regex_search(text, pat, boost::match_extra);
}

string removeFirstToken(string line)
{
    size_t i = line.find_first_of(" ");
    return line.substr(i+1);
}

bool containsMultipleArgs(string text)
{
    size_t dQuotes = 0;
    for (size_t i = 0; i < text.size(); i++) {
        if (text[i] == '\"') {
            dQuotes++;
            continue;
        }
        if (dQuotes >= 2 && dQuotes % 2 == 0 && text[i] == ',') return true;
    }
    return false;
}

void executePrint(string text)
{
    if (containsInnerVariables(text)) {
        vector<string> vars = extractInnerStrVariables(text);
        vars = dedup(vars);
        string line = removeFirstToken(text);
        cout << "log contains variable: " << line << endl;
        for (string var : vars) {
            cout << "\tVar: " << var << endl;
        }
    }
    else {
        if (text.starts_with("print")) {
            string argStr = removeFirstToken(text);
            if (containsMultipleArgs(argStr)) {
                cout << "print multiple args: " << argStr << endl;
            }
            else {
                if (contains(argStr, "\"")) {
                    string text = extractTextFromString(argStr);
                    cout << text;
                }
                else {
                    cout << "Printing variable: " << argStr << endl;
                }
            }
        }
        else {
            string argStr = removeFirstToken(text);
            if (containsMultipleArgs(argStr)) {
                cout << "puts multiple args: " << argStr << endl;
            }
            else {
                if (contains(argStr, "\"")) {
                    string text = extractTextFromString(argStr);
                    cout << text << endl;
                }
                else {
                    cout << "Printing variable with newline: " << argStr << endl;
                }
            }
        }
    }
}

/*
* Complications:
* - Variables may be passed before they exist.
*     - Panic.
* - DQuotes may be unmatched.
*     - Panic.
* - Strings may contain escaped characters.
*     - Handle per case.
* - Escaped characters (currently) include: \", \r, \n, \t, \\.
*/
