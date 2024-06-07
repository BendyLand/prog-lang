package utils

func Contains[T comparable](coll []T, item T) bool {
	for _, val := range coll {
		if item == val {
			return true
		}
	}
	return false
}