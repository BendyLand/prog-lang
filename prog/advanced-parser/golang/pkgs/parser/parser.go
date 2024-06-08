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

func CheckSingleLineStatement(line[]S) bool {
	var result bool
	switch line[0] {
	case LET, PUTS, PRINT:
		result = true
	default:
		result = false
	}
	return result
}

func GroupSingleLineStatement(line []S) []S {
	var result []S
	result = append(result, line[0])
	args := strings.Split(string(line[1]), "=")
	for _, arg := range args {
		arg = strings.Trim(arg, " ")
		result = append(result, S(arg))
	}
	return result
}

func GroupLines(tokenizedLines [][]S, groupedLines *[][]S) {
	for i, line := range tokenizedLines {
		if CheckSingleLineStatement(line) {
			groupedLine := GroupSingleLineStatement(line)
			(*groupedLines)[i] = make([]S, len(groupedLine))
			(*groupedLines)[i] = groupedLine
		}
	}
}

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
