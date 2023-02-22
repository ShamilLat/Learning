package main

import "fmt"

func main() {
	arr := []string{"a", "b", "c"}

	// i - index, l - value
	for i, l := range arr {
		fmt.Println(i)
		fmt.Println(l)
	}

	fmt.Println()
	// Только индексы
	for i := range arr {
		fmt.Println(i)
	}

	fmt.Println()
	// Только значения
	for _, l := range arr {
		fmt.Println(l)
	}

	fmt.Println()
	val := make(map[string]bool)
	val["a"] = true
	val["b"] = true
	val["c"] = false
	val["d"] = true
	val["d"] = true
	val["d"] = true
	val["d"] = false
	for i := range val {
		fmt.Println(i)
	}
}
