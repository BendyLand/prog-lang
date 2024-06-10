package main

import "lexer"
import "core:fmt"

main :: proc() {
    file := lexer.read_file("../../../test.pr")
	test := lexer.remove_comments(file)
    fmt.println(test)
}
