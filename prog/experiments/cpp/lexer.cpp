#include "lexer.hpp" // "utils.hpp" -> iostream, string, fstream, vector

using namespace std;

string prepareFile(string file)
{
    file = removeComments(file);
    file = normalize(file);
    file = removeEmptyLines(file);
    return file;
}

string normalize(string file)
{
    string result = "";
    vector<string> lines = strSplit(file, "\n");
    for (string line : lines) {
        string temp = lstrip(line);
        result += temp + "\n";
    }
    return result;
}

string removeComments(string file)
{
    string result = "";
    vector<string> lines = strSplit(file, "\n");
    for (string line : lines) {
        if (line.find("#") != string::npos) {
            size_t comment = line.find("#");
            if (containsEmbeddedString(line)) {
                size_t start = line.find_first_of("\"");
                size_t end = line.find_last_of("\"");
                if (comment > start && comment < end) {
                    result += line + "\n";
                    continue; //! currently cannot place comments after strings that contain '#'
                }
            }
            string temp = line.substr(0, comment);
            result += temp + "\n";
        }
        else {
            result += line + "\n";
        }
    }
    return result;
}

string removeEmptyLines(string file)
{
    vector<string> lines = strSplit(file, "\n");
    string result = "";
    for (string line : lines) {
        if (line.empty()) continue;
        result += line + "\n";
    }
    return result;
}