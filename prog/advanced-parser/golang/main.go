package main

import (
	"fmt"
	"os"
)

func main() {
	file := readFile("../../../test.pr")
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
