package variables

import (
	"advanced-parser/golang/pkgs/parser"
	"fmt"
)

func ShowVariableType(val any) {
	fmt.Printf("%T\n", val)
}

func ShowVariables(vars map[string]any) {
	for name, val := range vars {
		fmt.Printf("%s: %v\n", name, val)
	}
}

func AssignVariables(lines [][] parser.Str) map[string]any {
	result := make(map[string]any)
	Loop: for _, line := range lines {
		if len(line) > 0 {
			switch line[0] {
			case parser.LET:
				result[string(line[1])] = line[2]
			default:
				continue Loop
			}
		}
	}
	return result
}