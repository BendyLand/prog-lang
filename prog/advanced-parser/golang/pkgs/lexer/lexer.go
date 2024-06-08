package lexer

import (
	"strings"
)

func Normalize(file string) string {
	result := ""
	lines := strings.Split(file, "\n")
	for _, line := range lines {
		line = strings.Trim(line, "\t ")
		result += line + "\n"
	}
	return result
}

func RemoveEmptyLines(file string) string {
	result := ""
	lines := strings.Split(file, "\n")
	for _, line := range lines {
		if len(line) == 0 {
			continue
		}
		result += line + "\n"
	}
	temp := strings.Split(result, "\n")
	temp = temp[:len(temp)-1]
	result = strings.Join(temp, "\n")
	return result
}

func RemoveComments(file string) string {
	result := ""
	lines := strings.Split(file, "\n")
	for _, line := range lines {
		hasComment := false
		quoteCount := 0
		for _, c := range line {
			if c == '"' {
				quoteCount++
			}
			if quoteCount == 1 {
				continue
			}
			if c == '#' {
				hasComment = true
			}
		}
		if hasComment {
			commentIdx := strings.Index(line, "#")
			line = line[:commentIdx]
		}
		result += line + "\n"
	}
	return result
}