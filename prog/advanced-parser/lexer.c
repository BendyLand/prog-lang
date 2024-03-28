#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* getFileContents();
int splitIntoLines(char**, char*);
void removeComments(char**);
void tokenizeString(char*, char*);
int containsValidString(char*);
void tokenizeLine(char**, char*);
void tokenizeStringLine(char**, char*);
void tokenizeNonStringLine(char**, char*);
void trimLeadingWhitespace(char*);

/** 
 * Moves non-whitespace characters to the front of the buffer.
 * @param line The line of text to trim. 
 */ 
void trimLeadingWhitespace(char* line)
{
    size_t start = 0;
    size_t length = strlen(line);
    while (line[start] == ' ' && start < length)
        start++;
    if (start > 0)
        memmove(line, line+start, length-start+1);
}
/**
 * A helper function for `tokenizeLine`. 
 * This function is called when a valid string is NOT detected in the input line. 
 * @param dest The destination to copy the tokens to. 
 * @param line The line to split into tokens. 
 *             This will be passed through from `tokenizeLine`.
 */ 
void tokenizeNonStringLine(char** dest, char* line)
{
    int length = strlen(line);
    char* temp = (char*)malloc(length);
    int i = 0;
    int j = 0;
    int n = 0;
    while (line[i] != '\0') {
        if (line[i] == ' ') {
            trimLeadingWhitespace(temp);
            dest[n] = strdup(temp);
            j = 0;
            memset(temp, 0, length);
            n++;
        }
        temp[j] = line[i];
        i++;
        j++;
    }
    if (j > 0) {
        trimLeadingWhitespace(temp);
        dest[n] = strdup(temp);
    }
    dest[n+1] = NULL;
    free(temp);
}

/**
 * A helper function for `tokenizeLine`. 
 * This function is called when a valid string is detected in the input line. 
 * @param dest The destination to copy the tokens to. 
 * @param line The line to split into tokens. 
 *             This will be passed through from `tokenizeLine`.
 */
void tokenizeStringLine(char** dest, char* line)
{
    int length = strlen(line);
    char* string = (char*)malloc(length);
    tokenizeString(string, line);

    char* temp = (char*)malloc(length);
    int i = 0;
    int j = 0;
    int n = 0;
    while (line[i] != '"') {
        if (line[i] == ' ') {
            trimLeadingWhitespace(temp);
            dest[n] = strdup(temp);
            j = 0;
            memset(temp, 0, length);
            n++;
        }
        temp[j] = line[i];
        i++;
        j++;
    }
    if (j > 0) {
        trimLeadingWhitespace(string);
        dest[n] = strdup(string);
    }
    dest[n+1] = NULL;
    free(string);
    free(temp);
}

/**
 * Splits a givens line of text into tokens based on their content.
 * @param dest The destination to copy the resulting tokens to. 
 *             This function assumes the outer pointer of `dest` is allocated.
 * @param line The line of test to split into tokens. 
 */
void tokenizeLine(char** dest, char* line)
{
    if (containsValidString(line))
        tokenizeStringLine(dest, line);
    else
        tokenizeNonStringLine(dest, line);
}

/**
 * Checks `line` for the presence of a valid string.
 * @param line The string to check for double quotes.
 * @return 1 if `line` contains two or more double quotes, otherwise 0.
 */
int containsValidString(char* line)
{
    int length = strlen(line);
    int quotes = 0;
    for (int i = 0; i < length; i++) {
        if (line[i] == '"')
            quotes++;
    }
    return quotes >= 2 ? 1 : 0;
}
/**
 * Copies any valid embedded string in `line` to `dest` as one token.
 * @param dest The destination to copy the embedded string to.
 *             This must be allocated before calling the function.
 * @param line The source text to check for double quotes.
 */
void tokenizeString(char* dest, char* line)
{
    int i = 0;
    char* stringStart = strchr(line, '"');
    int length = strlen(stringStart);
    char* stringLiteral = (char*)malloc(length+1);
    while (stringStart[i+1] != '"' || i > length) {
        if (stringStart[i+1] == '\\' && i < length - 1) {
            if (stringStart[i+2] == '"') {
                for (int n = 0; n < 2; n++) {
                    stringLiteral[i] = stringStart[i+1];
                    i++;
                }
                stringLiteral[i] = stringStart[i+1];
            }
            else if (stringStart[i+2] == 'n') {
                stringLiteral[i] = '\n';
                i += 2;
                continue;
            }
        }
        stringLiteral[i] = stringStart[i+1];
        i++;
    }
    stringLiteral[i] = '\0';
    strcpy(dest, stringLiteral);
    free(stringLiteral);
}

/**
 * Removes any characters including and after '//' from all lines.
 * @param buffer The source text to remove comments from.
 *               This should be a dynamic array of strings.
 */
void removeComments(char** buffer)
{
    int i = 0;
    while (buffer[i] != NULL) {
        int length = strlen(buffer[i]);
        for (int j = 0; j < length-1; j++) {
            if (buffer[i][j] == '/' && buffer[i][j+1] == '/') {
                buffer[i][j] = '\0';
                break;
            }
            // Otherwise nothing happens
        }
        i++;
    }
    buffer[i] = NULL;
}
/**
 * Splits `file` into a dynamic array of strings, stored in `buffer`.
 * @param buffer The destination to copy the split file into.
 *               The outer pointer should be allocated.
 *               The inner pointers will be allocated inside the function.
 * @param file The source text to split.
 * @return The number of lines that the file was split into.
 *         The caller is responsible for freeing the inner pointers of `buffer`.
 */
int splitIntoLines(char** buffer, char* file)
{
    int line = 0;
    int length = strlen(file);
    int j = 0;
    char* temp = (char*)malloc(101); // lines must be under 100 characters long
    char c;
    for (int i = 0; i < length; i++) {
        c = file[i];
        if (c == '\n' || i == length - 1) {
            temp[j] = '\0';
            buffer[line] = (char*)malloc(strlen(temp) + 1);
            if (buffer[line] == NULL) {
                perror("Error creating line buffer.\n");
                continue;
            }
            strcpy(buffer[line], temp);
            j = 0;
            line++;
        }
        else {
            temp[j] = c;
            j++;
        }
    }
    buffer[line] = NULL;
    free(temp);
    return line;
}

/**
 * Reads the contents of the file in the hard-coded path.
 * @return A dynamic string containing the file contents. 
 *         The caller is responsible for freeing it.
 */
char* getFileContents()
{
    FILE* fptr;
    long length;

    fptr = fopen("../../test.pr", "r");
    if (fptr == NULL) {
        perror("Problem opening file.\n");
        return NULL;
    }

    fseek(fptr, 0, SEEK_END);
    length = ftell(fptr);
    rewind(fptr);

    char* buffer = (char*)malloc(sizeof(char) * length + 1);
    if (buffer == NULL) {
        perror("Problem creating buffer");
        fclose(fptr);
        return NULL;
    }

    if (fread(buffer, sizeof(char), length, fptr) != length) {
        perror("Failed to read file.");
        fclose(fptr);
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    fclose(fptr);

    return buffer;
}
