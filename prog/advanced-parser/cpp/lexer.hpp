#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>
#include "tokens.hpp"

class Lexer
{
public:
    /** 
     * Constructs a new `Lexer` object. 
     * @param text The string to feed into the Lexer.
     */
    Lexer(std::string text);

    /**
     * Increases the index by 1 and updates the corresponding member elements. 
     * If the end of the is reached, nothing happens. 
     */
    void increment();

    /**
     * @return The current character of the input text.
     */
    char getCurrent();

    /**
     * @return The next character of the input text. 
     */
    char getNext();

    /**
     * @return The current index.
     */
    int getIndex();

    /**
     * @return The size of the input string. 
     */
    int size();

private:
    std::string _text;
    char _current;
    char _next;
    int _index;
    int _size;
};

/**
 * Reads the contents of the file specified with `path`.
 * @param path The path of the text file to read. 
 *             If no valid file exists at the path, an error message is printed.
 * @return The contents of the given file as a string. 
 *         If no valid file exists, an empty string is returned. 
 */
std::string readFile(std::string);

/**
 * Splits the provided string at newlines. 
 * @param file The input string to split.
 * @return The input file split at newlines, stored in a vector of strings. 
 */
std::vector<std::string> splitIntoLines(std::string);

/**
 * Removes comments from the input string.
 * @param line The source string to check for comments.
 * @return a new string with any comments removed.
 */
std::string removeComment(std::string);

#endif