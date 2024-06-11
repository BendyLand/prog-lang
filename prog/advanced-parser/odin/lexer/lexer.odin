package lexer

import "core:fmt"
import "core:os"
import "core:strings"

prep_file :: proc(file: string) -> string {
	file_no_comments := remove_comments(file)
    file_normalized := normalize(file_no_comments)
    file_fully_prepped := remove_empty_lines(file_normalized)
    return file_fully_prepped
}  

remove_empty_lines :: proc(file: string) -> string {
    lines := strings.split(file, "\n")
    result: strings.Builder
    for line in lines {
        if len(line) > 0 {
            strings.write_string(&result, line)
            strings.write_string(&result, "\n")
        }
    }
    result_str := strings.to_string(result)
    temp_lines := strings.split(result_str, "\n")
    temp_lines = temp_lines[:len(temp_lines)-1]
    result_str = strings.join(temp_lines, "\n")
    return result_str
}

normalize :: proc(file: string) -> string {
    lines := strings.split(file, "\n")
    result: strings.Builder
    for line in lines {
        temp := strings.trim(line, " ")
        strings.write_string(&result, temp)
        strings.write_string(&result, "\n")
    }
    result_str := strings.to_string(result)
    return result_str
}

remove_comments :: proc(file: string) -> string {
    lines := strings.split(file, "\n")
    result: strings.Builder
    for line in lines {
        if !strings.contains_rune(line, '#') {
            strings.write_string(&result, line)
            strings.write_string(&result, "\n")
            continue
        }
        has_d_quotes := false
        if strings.contains_rune(line, '"') {
            has_d_quotes = true
        }
        if has_d_quotes {
            is_embedded_hash := false
            i1 := strings.index(line, "\"")
            i2 := strings.last_index(line, "\"")
            i_hash := strings.index(line, "#")
            if i1 < i_hash && i2 > i_hash {
                is_embedded_hash = true
            }
            if is_embedded_hash {
                strings.write_string(&result, line)
                strings.write_string(&result, "\n")
                continue
            }
            idx := strings.index(line, "#")
            temp_str := line[:idx]
            strings.write_string(&result, temp_str)
            strings.write_string(&result, "\n")
        }
        else {
            idx := strings.index(line, "#")
            temp_str := line[:idx]
            strings.write_string(&result, temp_str)
            strings.write_string(&result, "\n")
        }
    }
    result_str := strings.to_string(result)
    return result_str
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