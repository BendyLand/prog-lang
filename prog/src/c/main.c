#include <unistd.h>
#include "lexer.h"
#include "utils.h"

int main(int argc, char** argv)
{
    string* file;
    if (argc > 1) {
        file = readFile(argv[1]);
    }
    else {
        file = readFile("test.pr");
    }
    stringArray* lines = strArr(file, "\n");
    string* preppedFile = prepareFile(&lines);
    puts(preppedFile->data);
    strFree(file);
    strFree(preppedFile);
    strArrFree(lines);
    // sleep(10);
    return 0;
}
