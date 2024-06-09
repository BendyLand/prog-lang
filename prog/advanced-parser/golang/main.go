package main

import (
	"advanced-parser/golang/pkgs/execution"
	"advanced-parser/golang/pkgs/lexer"
	"advanced-parser/golang/pkgs/parser"
	"advanced-parser/golang/pkgs/variables"
	"fmt"
	"os"
)

func main() {
	file := readFile("../../../test.pr")
	file = prepareFile(file)
	tokenizedLines := parser.TokenizeLines(file)
	groupedLines := make([][]parser.S, len(tokenizedLines))
	parser.GroupLines(tokenizedLines, &groupedLines)
	execution.SelectExecutables(groupedLines)
	vars := variables.AssignVariables(groupedLines)
	variables.ShowVariables(vars)
}

func prepareFile(file string) string {
	file = lexer.RemoveComments(file)
	file = lexer.Normalize(file)
	file = lexer.RemoveEmptyLines(file)
	return file
}

func readFile(path string) string {
	file, err := os.ReadFile(path)
	if err != nil {
		fmt.Println("Error reading file:", err)
		os.Exit(1)
	}
	return string(file)
}
