package execution

import (
	"fmt"
	"advanced-parser/golang/pkgs/parser"
)

func SelectExecutables(lines [][]parser.Str) {
	Loop: for _, line := range lines {
		if len(line) > 0 {
			switch line[0] {
			case "print":
				execPrint(line[1])
			case "puts":
				execPuts(line[1])
			default:
				continue Loop
			}
		}
	}
}

func execPrint(arg parser.Str) {
	fmt.Print(arg)
}

func execPuts(arg parser.Str) {
	fmt.Println(arg)
}