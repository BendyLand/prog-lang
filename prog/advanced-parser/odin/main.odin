package main

import "core:fmt"
import "core:os"
import "core:strings"


main :: proc() {
    fmt.println("Hello Odin parser!")
    file := read_file("../../../test.pr")
    fmt.println(file)
}

read_file :: proc(path: string) -> string {
	data, ok := os.read_entire_file(path)
	if !ok {
		fmt.println("Error reading file.")
		os.exit(1)
	}
	defer delete(data)

	it := string(data)
    result := ""
	for line in strings.split_lines_iterator(&it) {
		temp := strings.concatenate([]string{line, "\n"})
		result = strings.concatenate([]string{result, temp})
	}
    return result
}
