#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "keywords.h"

#define MAX_LINES 100

char* getFileContents();
int splitIntoLines(char**, char*);
void removeComments(char**);
void tokenizeString(char*, char*);
int containsValidString(char*);
void tokenizeLine(char** dest, char* line);

int main(void) {
    char* data = getFileContents();
    char** buffer = (char**)malloc(sizeof(char*) * (MAX_LINES + 1));
    memset(buffer, 0, sizeof(char*) * (MAX_LINES + 1));

    int numLines = splitIntoLines(buffer, data);
    char** lineTokens = (char**)malloc(sizeof(char*) * MAX_LINES + 1);
    removeComments(buffer);

    int i = 0;
    while (buffer[i] != NULL) {
        puts(buffer[i]);

        free(buffer[i]);
        i++;
    }
    free(buffer);
    free(data);

    return 0;
}

void tokenizeLine(char** dest, char* line) {

}

int containsValidString(char* line) {
    int length = strlen(line);
    int quotes = 0;
    for (int i = 0; i < length; i++) {
        if (line[i] == '"') {
            quotes++;
        }
    }
    return quotes >= 2 ? 1 : 0;
}

// This function copies any valid string in a line to `dest` as one token.
// It assumes `line` is an existing line, and `dest` is an already allocated buffer with equal or greater length
void tokenizeString(char* dest, char* line) {
    int i = 0;
    char* stringStart = strchr(line, '"');
    int length = strlen(stringStart);
    char stringLiteral[length+1];
    while (stringStart[i+1] != '"' || i > length) {
        stringLiteral[i] = stringStart[i+1];
        i++;
    }
    stringLiteral[i] = '\0';
    strcpy(dest, stringLiteral);
}

// This function assumes `buffer` is fully allocated and ends in NULL
void removeComments(char** buffer) {
    int i = 0;
    // Until there are no more lines...
    while (buffer[i] != NULL) {
        int length = strlen(buffer[i]);
        for (int j = 0; j < length-1; j++) {
            // If you encounter a comment...
            if (buffer[i][j] == '/' && buffer[i][j+1] == '/') {
                // Set the null byte to the start of the comment
                buffer[i][j] = '\0';
                break;
            }
            // Otherwise nothing happens
        }
        i++;
    }
    buffer[i] = NULL;
}

int splitIntoLines(char** buffer, char* file) {
    int line = 0;
    int length = strlen(file);
    int j = 0;
    char temp[100] = {0}; // lines must be under 100 characters long
    char c;
    // For each char in the file...
    for (int i = 0; i < length; i++) {
        c = file[i];
        // (End condition for each line) If you're on a newline or the final char...
        if (c == '\n' || i == length - 1) {
            // Set the null byte at the 'pointer' and copy the string into buffer
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
        else { // If it's NOT a newline or the last char...
            // Add the char to temp and increment the 'pointer'
            temp[j] = c;
            j++;
        }
    }
    // Set the last element of `buffer` to NULL
    buffer[line] = NULL;
    return line;
}

char* getFileContents() {
    FILE* fptr;
    long length;

    fptr = fopen("../../test.pr", "r");
    if (fptr == NULL) {
        perror("Problem opening file.\n");
        return NULL;
    }

    // Move the pointer to the end, get its index, and resent the pointer to the start
    fseek(fptr, 0, SEEK_END);
    length = ftell(fptr);
    rewind(fptr);

    // Create buffer and check for failed malloc
    char* buffer = (char*)malloc(sizeof(char) * length + 1);
    if (buffer == NULL) {
        perror("Problem creating buffer");
        fclose(fptr);
        return NULL;
    }

    // Try to copy file contents to buffer
    if (fread(buffer, sizeof(char), length, fptr) != length) {
        perror("Failed to read file.");
        fclose(fptr);
        // If file read fails, free buffer before returning
        free(buffer);
        return NULL;
    }

    // Set the end of buffer to a null byte and close the file
    buffer[length] = '\0';
    fclose(fptr);

    // If nothing fails, buffer must be freed by caller
    return buffer;
}