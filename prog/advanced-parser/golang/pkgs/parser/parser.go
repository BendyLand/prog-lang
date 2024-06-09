package parser

import (
	"strings"
)

type Str string

const (
	LET Str= "let"
	IF Str= "if"
	ELIF Str= "elif"
	ELSE Str= "else"
	FOR Str= "for"
	PUTS= "puts"
	PRINT Str= "print"
	OP_BRACE Str= "{"
	CL_BRACE Str= "}"
	UNKNOWN Str= ""
)

func CheckSingleLineStatement(line []Str) bool {
	var result bool
	switch line[0] {
	case LET, PUTS, PRINT:
		result = true
	default:
		result = false
	}
	return result
}

func GroupSingleLineStatement(line []Str) []Str{
	var result []Str
	result = append(result, line[0])
	args := strings.Split(string(line[1]), "=")
	for _, arg := range args {
		arg = strings.Trim(arg, " ")
		result = append(result, Str(arg))
	}
	return result
}

func GroupLines(tokenizedLines [][]Str, groupedLines *[][]Str) {
	for i, line := range tokenizedLines {
		if CheckSingleLineStatement(line) {
			groupedLine := GroupSingleLineStatement(line)
			(*groupedLines)[i] = make([]Str, len(groupedLine))
			(*groupedLines)[i] = groupedLine
		}
	}
}

func TokenizeLines(file string) [][]Str{
	lines := strings.Split(file, "\n")
	result := make([][]Str, len(lines))
	for i, line := range lines {
		firstSpace := strings.Index(line, " ")
		keyword := identifyKeyword(line)
		remainder := Str("")
		if len(line) > 2 {
			remainder = Str(line[firstSpace+1:])
		}

		result[i] = make([]Str, 2)
		result[i][0] = keyword
		result[i][1] = remainder
	}
	return result
}

func identifyKeyword(line string) Str{
	tokens := strings.Split(line, " ")
	if len(tokens) == 0 {
		return ""
	}
	var result Str
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
