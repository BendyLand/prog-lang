package utils

import ()

func Contains[T comparable](coll []T, item T) bool {
	for _, elem := range coll {
		if elem == item {
			return true
		}
	}
	return false
}
