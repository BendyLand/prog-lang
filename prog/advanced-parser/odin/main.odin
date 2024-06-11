package main

import "lexer"
import "core:fmt"

main :: proc() {
    file := lexer.read_file("../../../test.pr")
    file = lexer.prep_file(file)

    fmt.println(file)
}
