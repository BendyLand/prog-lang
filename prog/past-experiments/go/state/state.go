package state

import (
	"fmt"
	"os"
	"regexp"
)

type LineParser struct {
	CurrentChar rune
	NextChar    rune
	Index       int
	State       string
}

func parseStringLiteral(line string) string {
	pattern, err := regexp.Compile("\".*\"")
	if err != nil {
		fmt.Println("There was a problems creating the regex")
		os.Exit(1)
	}
	return pattern.FindString(line)
}

func (lp *LineParser) Parse(line string) []string {
	var tokens []string
	token := ""
	for i, current := range line {
		var next rune
		if i+1 < len(line) {
			next = rune(line[i+1])
		} else {
			next = '\n'
		}
		lp.UpdateState(i, current, next)
		switch lp.State {
		// PreParser became necessary as comments were not being properly handled with newlines alone.
		// The old version would include the last char of the comment as its own real token, which is wrong.
		// "PreParser" is a form of padding, however its use requires an end token on each line, i.e. semicolons.
		// Otherwise it will cut off the first char of the next valid line.
		case "PreParser":
			lp.State = "Parser"
		case "Parser":
			if current == ' ' {
				if token != "" {
					tokens = append(tokens, token)
					token = ""
				}
			} else {
				token += string(current)
			}
		case "StringLiteral":
			token += string(current)
		case "StringLiteralTerminator":
			tokens = append(tokens, token+string(current))
			token = ""
			lp.State = "PreParser"
		case "Comment":
			continue
		}
	}
	if token != "" {
		tokens = append(tokens, token)
	}
	return tokens
}

func (lp *LineParser) UpdateState(index int, current, next rune) {
	lp.Index = index
	lp.CurrentChar = current
	lp.NextChar = next

	// Check high priority cases first.
	switch {
	case lp.CurrentChar == '"' && lp.State != "StringLiteral":
		lp.State = "StringLiteral"
		return // Exit early to prevent state override.
	case lp.CurrentChar == '"' && lp.State == "StringLiteral":
		lp.State = "StringLiteralTerminator"
		return
	case lp.CurrentChar == '/' && lp.NextChar == '/' && lp.State != "StringLiteral":
		lp.State = "Comment"
		return
	}

	// Then handle state-specific transitions.
	switch lp.State {
	case "StringLiteralTerminator":
		lp.State = "Parser"
	case "Comment":
		if lp.NextChar == '\n' {
			lp.State = "PreParser"
		}
	}
}
