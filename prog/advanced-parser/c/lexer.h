/**
 * Reads the contents of the file in the hard-coded path.
 * @return A dynamic string containing the file contents. 
 *         The caller is responsible for freeing it.
 */
extern char* getFileContents();

/**
 * Splits `file` into a dynamic array of strings, stored in `buffer`.
 * @param buffer The destination to copy the split file into.
 *               The outer pointer should be allocated.
 *               The inner pointers will be allocated inside the function.
 * @param file The source text to split.
 * @return The number of lines that the file was split into.
 *         The caller is responsible for freeing the inner pointers of `buffer`.
 */
extern int splitIntoLines(char**, char*);

/**
 * Removes any characters including and after '//' from all lines.
 * @param buffer The source text to remove comments from.
 *               This should be a dynamic array of strings.
 */
extern void removeComments(char**);

/**
 * Copies any valid embedded string in `line` to `dest` as one token.
 * @param dest The destination to copy the embedded string to.
 *             This must be allocated before calling the function.
 * @param line The source text to check for double quotes.
 */
extern void tokenizeString(char*, char*);

/**
 * Checks `line` for the presence of a valid string.
 * @param line The string to check for double quotes.
 * @return 1 if `line` contains two or more double quotes, otherwise 0.
 */
extern int containsValidString(char*);

/**
 * Splits a givens line of text into tokens based on their content.
 * @param dest The destination to copy the resulting tokens to. 
 *             This function assumes the outer pointer of `dest` is allocated.
 * @param line The line of test to split into tokens. 
 */
extern void tokenizeLine(char**, char*);

/**
 * A helper function for `tokenizeLine`. 
 * This function is called when a valid string is detected in the input line. 
 * @param dest The destination to copy the tokens to. 
 * @param line The line to split into tokens. 
 *             This will be passed through from `tokenizeLine`.
 */
extern void tokenizeStringLine(char**, char*);

/**
 * A helper function for `tokenizeLine`. 
 * This function is called when a valid string is NOT detected in the input line. 
 * @param dest The destination to copy the tokens to. 
 * @param line The line to split into tokens. 
 *             This will be passed through from `tokenizeLine`.
 */ 
extern void tokenizeNonStringLine(char**, char*);

/** 
 * Moves non-whitespace characters to the front of the buffer.
 * @param line The line of text to trim. 
 */ 
extern void trimLeadingWhitespace(char*);