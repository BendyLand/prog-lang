#include "str.h" // stdio.h, stdlib.h, string.h
#include "utils.h"

// string* removeComments(string* file)
// {
//     string* result = str("");

// }

/*  
logic:
func RemoveComments(file string) string {
	result := ""
	lines := strings.Split(file, "\n")
	for _, line := range lines {
		hasComment := false
		quoteCount := 0
		for _, c := range line {
			if c == '"' {
				quoteCount++
			}
			if quoteCount == 1 {
				continue
			}
			if c == '#' {
				hasComment = true
			}
		}
		if hasComment {
			commentIdx := strings.Index(line, "#")
			line = line[:commentIdx]
		}
		result += line + "\n"
	}
	return result
}
*/

// normalize(file);
// removeEmptyLines(file);