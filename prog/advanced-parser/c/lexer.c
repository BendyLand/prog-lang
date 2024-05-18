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

void trimLeadingWhitespace(char* line)
{
    size_t start = 0;
    size_t length = strlen(line);
    while (line[start] == ' ' && start < length)
        start++;
    if (start > 0)
        memmove(line, line+start, length-start+1);
}

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

void tokenizeLine(char** dest, char* line)
{
    if (containsValidString(line))
        tokenizeStringLine(dest, line);
    else
        tokenizeNonStringLine(dest, line);
}

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

char* getFileContents()
{
    FILE* fptr;
    long length;

    fptr = fopen("../../../test.pr", "r");
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
