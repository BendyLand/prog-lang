package main

import "lexer"
import "core:fmt"

main :: proc() {
    file := lexer.read_file("../../../test.pr")
	file_no_comments := lexer.remove_comments(file)
    delete(file)
    file_normalized := lexer.normalize(file_no_comments)
    delete(file_no_comments)
    fmt.println(file_normalized)
}
