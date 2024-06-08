package main

import (
	"advanced-parser/golang/pkgs/lexer"
	"fmt"
	"os"
)

func main() {
	file := readFile("../../../test.pr")
	file = lexer.RemoveComments(file)
	file = lexer.Normalize(file)
	file = lexer.RemoveEmptyLines(file)
	fmt.Println(file)
}

func readFile(path string) string {
	file, err := os.ReadFile(path)
	if err != nil {
		fmt.Println("Error reading file:", err)
		os.Exit(1)
	}
	return string(file)
}
