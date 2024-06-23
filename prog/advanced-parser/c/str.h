#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Custom string type.
 * @param data The text of the string.
 * @param length The length of the string.
 */
typedef struct
{
    char* data;
    size_t length;
} string;



string* substr(string* original, size_t start, size_t end);

/** 
 * Constructor function for the string type.
 * @param text The text to convert to a string.
 * @returns A string* made from the input text.
 */  
string* str(const char* text);

/** 
 * Destructor function for the string type.
 * @param str The string* to be freed.
 */ 
void freeStr(string* str);

/** 
 * Function to append text to an existing variable of type string*.
 * @param original The base string. 
 * @param suffix The text you want to append onto the original.
 * @returns NOTHING. The text is appended to `original` in place. 
 */ 
void appendStr(string* original, char* suffix);

/** 
 * Function to empty the contents of the string.
 * @param str The string to clear.
 * @returns NOTHING. The contents of `str` are removed in place.
 */ 
void clearStr(string* str);

/** 
 * Checks if given string has any data.
 * @param str The string to check.
 * @returns A boolean value representing if the string is empty ("") or not.
 */  
bool isEmpty(string* str);

#endif
