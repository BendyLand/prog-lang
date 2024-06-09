#include "utils.h"

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