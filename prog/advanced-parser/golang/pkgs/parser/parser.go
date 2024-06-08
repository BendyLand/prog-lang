package parser

import (
	"strings"
)

type S string

const (
	LET S = "let"
	IF S = "if"
	ELIF S = "elif"
	ELSE S = "else"
	FOR S = "for"
	PUTS S = "puts"
	PRINT S = "print"
	OP_BRACE S = "{"
	CL_BRACE S = "}"
	UNKNOWN S = ""
)

func TokenizeLines(file string) [][]S {
	lines := strings.Split(file, "\n")
	result := make([][]S, len(lines))
	for i, line := range lines {
		firstSpace := strings.Index(line, " ")
		keyword := identifyKeyword(line)
		remainder := S("")
		if len(line) > 2 {
			remainder = S(line[firstSpace+1:])
		}

		result[i] = make([]S, 2)
		result[i][0] = keyword
		result[i][1] = remainder
	}
	return result
}

func identifyKeyword(line string) S {
	tokens := strings.Split(line, " ")
	if len(tokens) == 0 {
		return ""
	}
	var result S
	switch tokens[0] {
	case "let":
		result = LET
	case "if":
		result = IF
	case "elif":
		result = ELIF
	case "else":
		result = ELSE
	case "for":
		result = FOR
	case "puts":
		result = PUTS
	case "print":
		result = PRINT
	case "{":
		result = OP_BRACE
	case "}":
		result = CL_BRACE
	default:
		result = UNKNOWN
	}
	return result
}
