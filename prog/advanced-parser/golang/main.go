package main

import (
	"advanced-parser/golang/pkgs/lexer"
	"advanced-parser/golang/pkgs/parser"
	"fmt"
	"os"
)

func main() {
	file := readFile("../../../test.pr")
	file = lexer.RemoveComments(file)
	file = lexer.Normalize(file)
	file = lexer.RemoveEmptyLines(file)
	tokenizedLines := parser.TokenizeLines(file)
	for _, line := range tokenizedLines {
		fmt.Println(line)
	}
}

func readFile(path string) string {
	file, err := os.ReadFile(path)
	if err != nil {
		fmt.Println("Error reading file:", err)
		os.Exit(1)
	}
	return string(file)
}
