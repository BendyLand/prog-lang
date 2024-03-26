extern char* getFileContents();
extern int splitIntoLines(char**, char*);
extern void removeComments(char**);
extern void tokenizeString(char*, char*);
extern int containsValidString(char*);
extern void tokenizeLine(char**, char*);
extern void tokenizeStringLine(char**, char*);
extern void tokenizeNonStringLine(char**, char*);
extern void trimLeadingWhitespace(char*);