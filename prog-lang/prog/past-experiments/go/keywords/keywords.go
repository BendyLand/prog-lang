package keywords

import (
	"fmt"
)

type Token string
type Tokens []string

func (t *Token) contains(val rune) bool {
	for _, c := range *t {
		if c == val {
			return true
		}
	}
	return false
}

func ParseVariableToken(tokens Tokens) (map[Token]Token, error) {
	var name, value Token
	isValue := false
	for i, token := range tokens {
		switch {
		case i == 0 && token != "let": // possibly redundant; this is called if the first token == "let"
			return nil, fmt.Errorf("Error: Not a variable binding.\n")
		case i == 1:
			name = Token(token)
		case token == "=":
			isValue = true
		case token == ";":
			isValue = false
		case isValue:
			value += Token(token)
		}
	}
	result := map[Token]Token{name: value}
	return result, nil
}

func ParsePutsFn(tokens []string) (string, error) {
	for i, token := range tokens {
		if i > 1 {
			continue
		} // temporary handling of extra tokens; will need to refactor to handle string interpolation
		if len(tokens) > 1 {
			switch {
			case i == 0 && token != "puts":
				return "", fmt.Errorf("Error: Not a `puts` function.\n")
			case i != 0 && token[0] != '"' && token[len(tokens)-1] != '"':
				return "", fmt.Errorf("Error: Argument not a string\n")
			}
			return tokens[1], nil
		}
	}
	return "\n", nil
}

func ParsePrintFn(tokens []string) (string, error) {
	for i, token := range tokens {
		if i > 1 {
			continue
		} // same as line 11; temporary fix
		switch {
		case i == 0 && token != "print":
			return "", fmt.Errorf("Error: Not a `print` function.\n")
		case i != 0 && token[0] != '"' && token[len(tokens)-1] != '"':
			return "", fmt.Errorf("Error: Argument not a string.\n")
		}
	}
	return tokens[1], nil
}
