#include "str.h" // stdio.h, stdlib.h, string.h, stdbool.h

/** 
 * Attempts to read the given file to a string.
 * @param path The path of the file to try reading. An invalid path will cause an error. 
 * @returns The contents of the file as a string* type.
 */  
string* readFile(char* path);
string* removeComments(string** arr);
void lstrip(string* original);
